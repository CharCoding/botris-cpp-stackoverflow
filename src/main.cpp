
#include "api/botris_api.hpp"

int main() {
  auto secrets = botris::get_secrets();

  botris::start(secrets,
    [&](const nlohmann::json&) { // moveHandler
      std::vector<botris::api::Move> moves {botris::api::Move::DASLeft};
      botris::api::sendMove(moves);
    }
  );

  int s;
  std::cin >> s;

  // for (int i = 0; i < 3; i++) {
  //   botris::webSocket.send("{"
  //                          "\"type\": \"action\","
  //                          "\"payload\": {"
  //                          "\"commands\":"
  //                          "[ \"sonic_drop\" ]"
  //                          "}"
  //                          "}");
  // }

  return 0;
}