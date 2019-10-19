#include "h_greedy_relaxed_plan.h"

#include "../option_parser.h"
#include "../plugin.h"

using namespace std;

namespace planopt_heuristics {
GreedyRelaxedPlanHeuristic::GreedyRelaxedPlanHeuristic(const options::Options &options)
    : Heuristic(options),
      relaxed_task(task_proxy) {
}

int GreedyRelaxedPlanHeuristic::compute_heuristic(const GlobalState &state) {
    relaxed_task.initial_state = relaxed_task.translate_state(state);

    vector<bool> proposition_reached(relaxed_task.propositions.size(), false);
    vector<bool> operator_used(relaxed_task.operators.size(), false);
    for (PropositionID id : relaxed_task.initial_state) {
        proposition_reached[id] = true;
    }

    // TODO: add your code for exercise 1 (c) here.
    return DEAD_END;
}

static Heuristic *_parse(OptionParser &parser) {
    Heuristic::add_options_to_parser(parser);
    Options opts = parser.parse();
    if (parser.dry_run())
        return 0;
    else
        return new GreedyRelaxedPlanHeuristic(opts);
}

static Plugin<Heuristic> _plugin("planopt_greedy_relaxed", _parse);

}
