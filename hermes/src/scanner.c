#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include "scanner.h"
#include "hlog.h"

////////////////////////////////////////////
#define ADDR_LEN 19
#define NAME_LEN 248

////////////////////////////////////////////
// Default hosts for bluetooth connection
static char* desired_host = "any";
static int num_hosts = 1;

////////////////////////////////////////////
void set_desired_host(char* host) {
  desired_host = host;
}

////////////////////////////////////////////
int scan() {
  inquiry_info *ii = NULL;
  int max_rsp, num_rsp;
  int dev_id, sock, len, flags;

  char addr[19] = { 0 };
  char name[248] = { 0 };

  // Check if we can just get the first connection
  if (!strcmp(desired_host, "any")) {
    dev_id = hci_get_route(NULL);
  } else {
    bdaddr_t host;
    str2ba(desired_host, &host);
    dev_id = hci_get_route(&host);
  }

  sock = hci_open_dev(dev_id);
  if (dev_id < 0 || sock < 0) {
    LOG_ERROR("Failed to create socket");
    perror("hci socket");
    return EXIT_FAILURE;
  }

  len = 8;
  max_rsp = 255;
  flags = IREQ_CACHE_FLUSH;
  ii = (inquiry_info*) malloc(max_rsp * sizeof(inquiry_info));

  num_rsp = hci_inquiry(dev_id, len, max_rsp, NULL, &ii, flags);
  if (num_rsp < 0) {
    LOG_ERROR("HCI INQUIRY FAILED");
    perror("hci_inquiry");
  }

  for (int i = 0; i < num_rsp; ++i) {
    LOG_INFO("Scanning found devices");
    ba2str(&(ii + i)->bdaddr, addr);
    memset(name, 0, sizeof(name));

    if (hci_read_remote_name(sock, &(ii + i)->bdaddr, sizeof(name),
          name, 0) < 0) {
      LOG_INFO("Failed to find name");
      strcpy(name, "[unknown]");
    }

    printf("%s  %s\n", addr, name);
  }

  free(ii);
  close(sock);

  return EXIT_SUCCESS;
}
