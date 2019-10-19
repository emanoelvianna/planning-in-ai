#include "h_add.h"

#include "../option_parser.h"
#include "../plugin.h"

using namespace std;

namespace planopt_heuristics {
HAddHeuristic::HAddHeuristic(const options::Options &options)
    : Heuristic(options),
      relaxed_task_graph(task_proxy) {
}

int HAddHeuristic::compute_heuristic(const GlobalState &global_state) {
    relaxed_task_graph.change_initial_state(global_state);
    if (relaxed_task_graph.is_goal_relaxed_reachable()) {
        return relaxed_task_graph.additive_cost_of_goal();
    } else {
        return DEAD_END;
    }
}

static Heuristic *_parse(OptionParser &parser) {
    Heuristic::add_options_to_parser(parser);
    Options opts = parser.parse();
    if (parser.dry_run())
        return nullptr;
    else
        return new HAddHeuristic(opts);
}

static Plugin<Heuristic> _plugin("planopt_add", _parse);

}
