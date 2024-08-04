
#include "botris.hpp"

int main() {
  auto secrets = botris::get_secrets();

  botris::wss_connect(secrets);

  int s;
  std::cin >> s;

  botris::webSocket.send(
      "{"
      "\"type\": \"action\","
      "\"payload\": {"
      "\"commands\":"
      "[ \"sonic_drop\", \"sonic_drop\", \"sonic_drop\" ]"
      "}"
      "}");

  return 0;
}