#ifndef SATSOLVER_H
#define SATSOLVER_H

#define SATSOLVER_SATISFIABLE 10
#define SATSOLVER_UNSATISFIABLE 20
#define SATSOLVER_UNKNOWN 0

#define SOLVER_PICOSAT_PUSH_POP 1
#define SOLVER_PICOSAT_ASSUMPTIONS 2
#define SOLVER_MINISAT 3
#define SOLVER_CRYPTOMINISAT 4
#define SOLVER_LINGELING_ASSUMPTIONS 5

// Use on of the following 4 sat solvers

//#define USE_SOLVER SOLVER_MINISAT
//#define USE_SOLVER SOLVER_CRYPTOMINISAT
//#define USE_SOLVER SOLVER_PICOSAT_ASSUMPTIONS
#define USE_SOLVER SOLVER_PICOSAT_PUSH_POP
//#define USE_SOLVER SOLVER_LINGELING_ASSUMPTIONS

#ifndef USE_SOLVER // sanity check
    #error "No SAT solver selected. See file satsolver.h"
#endif

#include <stdbool.h>
#include "vector.h"

struct SATSolver;
typedef struct SATSolver SATSolver;

typedef enum {
    SATSOLVER_RESULT_UNKNOWN = SATSOLVER_UNKNOWN,
    SATSOLVER_RESULT_SAT     = SATSOLVER_SATISFIABLE,
    SATSOLVER_RESULT_UNSAT   = SATSOLVER_UNSATISFIABLE
} sat_res;

SATSolver* satsolver_init();
void satsolver_free(SATSolver*);
void satsolver_adjust(SATSolver* solver, int variables);
void satsolver_save_original_clauses(SATSolver* solver);
sat_res satsolver_state(SATSolver* solver);

void satsolver_clause_finished(SATSolver*);
void satsolver_clause_finished_for_context(SATSolver*, unsigned context_index);
int  satsolver_inc_max_var(SATSolver*);
void satsolver_set_max_var(SATSolver*, int new_max);
int satsolver_get_max_var(SATSolver*);
void satsolver_add(SATSolver*, int lit);
void satsolver_assume(SATSolver*, int lit);
void satsolver_clear_assumptions(SATSolver*);
bool satsolver_inconsistent(SATSolver*);
sat_res satsolver_sat(SATSolver*);
int satsolver_deref(SATSolver*, int lit);
int satsolver_deref_partial(SATSolver*, int lit);
int satsolver_deref_toplevel(SATSolver*, int lit);
int satsolver_is_decision_var(SATSolver*, int lit);
bool satsolver_failed_assumption(SATSolver*, int lit);
void satsolver_failed_assumptions(SATSolver*, int_vector*);

void satsolver_push(SATSolver*);
void satsolver_pop(SATSolver*);

void satsolver_set_more_important_lit (SATSolver*, int lit);

const int* satsolver_next_maximal_satisfiable_subset_of_assumptions(SATSolver* solver);

void satsolver_set_global_default_phase(SATSolver* s, int phase);
void satsolver_set_default_phase_lit (SATSolver* s, int lit, int phase);

void satsolver_print(SATSolver*);
void satsolver_print_translation_table(SATSolver*);
void satsolver_print_statistics(SATSolver*);

// for debugging picosat, only available if preprocessing flag SATSOLVER_TRACE is set
void satsolver_trace_commands(SATSolver*);

void satsolver_measure_all_calls(SATSolver*);
double satsolver_seconds(SATSolver*);

#endif
