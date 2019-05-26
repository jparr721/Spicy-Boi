#ifndef SCANNER_H_
#define SCANNER_H_

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
namespace hermes {
extern "C" {
#endif

//////////////////////////////////
struct scanner_log_event {
  bool enabled;
  float log_code;
  uint8_t log_level;
};
//////////////////////////////////
void set_desired_host(char* host);

//////////////////////////////////
int scan();

#ifdef __cplusplus
}
} // namespace hermes
#endif

#endif
