#include "downstack.hpp"
#include "pc.hpp"
#include "stride90.hpp"

#define FOR_EACH_STRATEGY(m)                                                   \
  do {                                                                         \
    m(PC);                                                                     \
    m(Stride90);                                                               \
    m(Downstack);                                                              \
  } while (0)

class Arbiter {
public:
  void choose() {
    // for each type of strategy, invoke
    std::vector<std::vector<Move>> results;
#define ADD_RESULT(res)                                                        \
  do {                                                                         \
    results.emplace_back(res::search());                                       \
  } while (0)
    FOR_EACH_STRATEGY(ADD_RESULT);
#undef ADD_RESULT
  }

private:
  vector<Move> bestMovesSoFar;
};