#ifndef PLANOPT_HEURISTICS_H_GREEDY_RELAXED_PLAN_H
#define PLANOPT_HEURISTICS_H_GREEDY_RELAXED_PLAN_H

#include "relaxed_task.h"

#include "../heuristic.h"

namespace planopt_heuristics {
class GreedyRelaxedPlanHeuristic : public Heuristic {
    RelaxedTask relaxed_task;
protected:
    virtual int compute_heuristic(const GlobalState &state) override;
public:
    explicit GreedyRelaxedPlanHeuristic(const options::Options &options);
};
}

#endif
