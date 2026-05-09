#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <memory>

struct ISolution
{
    virtual ~ISolution() = default;
};

class IEvaluator
{
public:
    virtual ~IEvaluator() = default;

    virtual std::shared_ptr<ISolution> initialSolution() const = 0;

    virtual std::shared_ptr<ISolution> getNeighbor(ISolution& currentSolution) const = 0;

    virtual void evaluate(ISolution& solution) const = 0;
};

#endif // EVALUATOR_H
