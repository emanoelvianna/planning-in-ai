#include "relaxed_task_graph.h"

#include <iostream>
#include <vector>

using namespace std;

namespace planopt_heuristics {
    RelaxedTaskGraph::RelaxedTaskGraph(const TaskProxy &task_proxy)
            : relaxed_task(task_proxy),
              variable_node_ids(relaxed_task.propositions.size()) {

        // Add an OR node for each proposition
        for (auto proposition : relaxed_task.propositions) {
            this->variable_node_ids[proposition.id] = this->graph.add_node(NodeType::OR);
            // cout << "Added node " << this->variable_node_ids[proposition.id] << endl;
        }

        // Add an AND node (I) and an edge from each initial node to I
        this->initial_node_id = this->graph.add_node(NodeType::AND);
        // cout << "INITIAL IS " << this->initial_node_id << endl;
        for (auto id : relaxed_task.initial_state) {
            this->graph.add_edge(this->variable_node_ids[id], this->initial_node_id);
            // cout << "Added an edge from " << this->variable_node_ids[id] << " to " << this->initial_node_id << endl;
        }

        // Add an AND node (G) and an edge from G to each goal node
        this->goal_node_id = this->graph.add_node(NodeType::AND);
        // cout << "GOAL IS " << this->goal_node_id << endl;
        for (auto id : relaxed_task.goal) {
            this->graph.add_edge(this->goal_node_id, this->variable_node_ids[id]);
            // cout << "Nodes to GOAL: " << this->variable_node_ids[id] << endl;
            // cout << "Added an edge from " <<this->goal_node_id  << " to " << this->variable_node_ids[id] << endl;
        }

        // Add an AND node (O) for each operation
        for (auto operation : relaxed_task.operators) {
            auto operation_id = this->graph.add_node(NodeType::AND, operation.cost);
            // cout << "Added operation " << operation_id << endl;

            // Add an edge from O to each operation pre condition
            for (auto precond_id : operation.preconditions) {
                this->graph.add_edge(operation_id, this->variable_node_ids[precond_id]);
                ///cout << "Added an edge from " << operation_id << " to " << this->variable_node_ids[precond_id] << endl;
            }

            // Add an edge from each operation effect to O
            for (auto effect_id : operation.effects) {
                this->graph.add_edge(this->variable_node_ids[effect_id], operation_id);
                // cout << "Added an edge from " << this->variable_node_ids[effect_id] << " to " << operation_id << endl;
            }
        }
    }

    void RelaxedTaskGraph::change_initial_state(const GlobalState &global_state) {
        // Remove all initial edges that where introduced for relaxed_task.initial_state.
        for (PropositionID id : relaxed_task.initial_state) {
            graph.remove_edge(variable_node_ids[id], initial_node_id);
        }

        // Switch initial state of relaxed_task
        relaxed_task.initial_state = relaxed_task.translate_state(global_state);

        // Add all initial edges for relaxed_task.initial_state.
        for (PropositionID id : relaxed_task.initial_state) {
            graph.add_edge(variable_node_ids[id], initial_node_id);
        }
    }

    bool RelaxedTaskGraph::is_goal_relaxed_reachable() {
        this->graph.most_conservative_valuation();
        auto goal_node = this->graph.get_node(this->goal_node_id);
        return goal_node.forced_true;
    }

    int RelaxedTaskGraph::additive_cost_of_goal() {
        // Compute the weighted most conservative valuation of the graph and use it
        // to return the h^add value of the goal node.

        // cout << "GOAL ID is " << this->goal_node_id << endl;
        this->graph.weighted_most_conservative_valuation();
        auto goal_node = this->graph.get_node(this->goal_node_id);
        return goal_node.additive_cost;
    }

    void RelaxedTaskGraph::process_achievers(NodeID id) {

        auto node = this->graph.get_node(id);
        if (this->visitedIds.find(id) == this->visitedIds.end()) {
            this->achievers_cost += node.direct_cost;
            this->visitedIds.insert(id);
        }
        if (node.type == NodeType::OR) {
            this->process_achievers(node.achiever);
        } else {
            for (auto succ_id : node.successor_ids) {
                this->process_achievers(succ_id);
            }
        }
    }

    int RelaxedTaskGraph::ff_cost_of_goal() {
        this->graph.weighted_most_conservative_valuation();
        this->achievers_cost = 0;
        this->visitedIds.clear();
        this->process_achievers(this->goal_node_id);
        return this->achievers_cost;
    }
}