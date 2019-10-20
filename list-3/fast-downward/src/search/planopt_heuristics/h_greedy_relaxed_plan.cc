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

        int cost = 0;
        while (true) {
            //PASSO 1: INICIO
            //  testa se estado atual satisfaz goal
            bool goal_satisfied = true;
            for (PropositionID id : relaxed_task.goal) {
                if (proposition_reached[id] == false) {
                    goal_satisfied = false;
                    break;
                }
            }
            if (goal_satisfied)
                return cost;
            //PASSO 1: FIM

            //PASSO 2: INICIO
            //  descobre se tem algum operador o em relaxed_task.operators aplicavel em s e que leve a um estado s' diferente de s
            bool applied = false;
            for (RelaxedOperator o : relaxed_task.operators) {
                bool applicable = true;
                for (PropositionID id : o.preconditions) {
                    if (proposition_reached[id] ==
                        false) { // se alguma pre-condicao nao faz parte do estado atual, operador nao eh aplicavel
                        applicable = false;
                        break;
                    }
                }
                if (applicable) {
                    for (PropositionID id : o.effects) {
                        if (proposition_reached[id] ==
                            false) { // primeiro operador que adiciona uma variavel nova ao estado eh aplicado
                            proposition_reached[id] = true;
                            operator_used[o.id] = true;
                            applied = true;
                        }
                    }
                }
                if (applied) {
                    cost = cost + o.cost;
                    break; // nao analisa operadores seguintes, uma vez que ja aplicamos um operador ao estado atual e devemos checar se chegamos ao objetivo
                }
            }
            //PASSO 2: FIM

            //PASSO 3: INICIO
            //  se nenhum dos operadores aplicaveis levou s a s', com s' diferente de s, retorna sem solucao
            if (applied == false)
                return DEAD_END;
            //PASSO 3: INICIO

        }
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
