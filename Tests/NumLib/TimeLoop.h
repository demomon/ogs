#pragma once

#include "TimeDiscretizedODESystem.h"

template<NonlinearSolverTag NLTag, typename TimeDisc>
class TimeLoop
{
public:
    using TDiscODESys = TimeDiscretizedODESystem<NLTag, TimeDisc>;
    using NLSolver = NonlinearSolver<NLTag>;

    TimeLoop(TDiscODESys& ode_sys, NLSolver nonlinear_solver)
        : _ode_sys(ode_sys)
        , _nonlinear_solver(nonlinear_solver)
    {}

    template<typename Callback>
    void loop(const double t0, const Vector x0,
              const double t_end, const double delta_t,
              Callback& post_timestep);

private:
    TDiscODESys& _ode_sys;
    NLSolver& _nonlinear_solver;
};


template<NonlinearSolverTag NLTag, typename TimeDisc>
template<typename Callback>
void
TimeLoop<NLTag, TimeDisc>::
loop(const double t0, const Vector x0, const double t_end, const double delta_t,
     Callback& post_timestep)
{
    Vector x(x0); // solution vector

    _ode_sys.setInitialState(t0, x0); // push IC

    if (_ode_sys.needsPreload()) {
        _nonlinear_solver.assemble(_ode_sys, x);
        _ode_sys.pushState(t0, x0, _ode_sys); // TODO: that might do duplicate work
    }

    for (double t=t0+delta_t; t<=t_end; t+=delta_t)
    {
        INFO("time: %e, delta_t: %e", t, delta_t);
        _ode_sys.setCurrentTime(t, delta_t);

        _nonlinear_solver.solve(_ode_sys, x);

        _ode_sys.pushState(t, x, _ode_sys);

        post_timestep(t, x);
    }
}