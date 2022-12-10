/*
 * FakeBotnet.mod
 * Version 1.4
 * By Wcc
 * wcc@techmonkeys.org
 *
 * This module provides dcc commands for broadcasting fake
 * botnet messages.
 *
 * Copyright © 2000 - 2002 |DAWG| Scripting Group. All rights reserved.
 *
 */

#define MODULE_NAME "fakebotnet"
#define MAKING_FAKEBOTNET
#define FAKEBOTNET_MAJORV 1
#define FAKEBOTNET_MINORV 4
#include "src/mod/module.h"
#include <stdlib.h>
#undef global

static Function *global = NULL;

char *fakebotnet_start();

static int fakebotnet_expmem()
{
  return 0;
}

static void fakebotnet_report(int idx, int details)
{
  if (details)
    dprintf(idx, "   FakeBotnet.mod v%d.%d by Wcc modified by pseudo.\n", FAKEBOTNET_MAJORV, FAKEBOTNET_MINORV);
}

static void cmd_flink(struct userrec *u, int idx, char *par)
{
  char *bot, msg[401];

  if (!par[0])
    dprintf(idx, "Usage: flink <bot/fake bot>\n");

  bot = newsplit(&par);
  snprintf(msg, sizeof msg, "Linked to %s.", bot);
  chatout("*** %s\n", msg);
  botnet_send_chat(-1, botnetnick, msg);
}

static void cmd_funlink(struct userrec *u, int idx, char *par)
{
  char *bot, msg[401];

  if (!par[0])
    dprintf(idx, "Usage: funlink <bot/fake bot>\n");
    
  bot = newsplit(&par);
  snprintf(msg, sizeof msg, "Unlinked from: %s (lost 1 bot and 0 users).", bot);
  chatout("*** %s\n", msg);
  botnet_send_chat(-1, botnetnick, msg);
}

static void cmd_fjoined(struct userrec *u, int idx, char *par)
{
  char *user, msg[401];

  if (!par[0])
    dprintf(idx, "Usage: fjoined <user/fake user>\n");
    
  user = newsplit(&par);
  snprintf(msg, sizeof msg, "%s has joined the party line.", user);
  chatout("*** %s\n", msg);
  botnet_send_chat(-1, botnetnick, msg);
}

static void cmd_fleft(struct userrec *u, int idx, char *par)
{
  char *user, msg[401];
    
  if (!par[0])
    dprintf(idx, "Usage: fleft <user/fake user>\n");
    
  user = newsplit(&par);
  snprintf(msg, sizeof msg, "%s has left the party line (lost dcc link).", user);
  chatout("*** %s\n", msg);
  botnet_send_chat(-1, botnetnick, msg);
}

static void cmd_fmsg(struct userrec *u, int idx, char *par)
{
  char msg[401];

  if (!par[0])
    dprintf(idx, "Usage: fmsg <message/fake message>\n");

  strncpyz(msg, par, sizeof msg);
  chatout("*** %s\n", msg);
  botnet_send_chat(-1, botnetnick, msg);
}

static cmd_t fakebotnet_dcc[] =
{
  {"flink",     "n",    (IntFunc) cmd_flink,       NULL},
  {"funlink",   "n",    (IntFunc) cmd_funlink,     NULL},
  {"fjoined",   "n",    (IntFunc) cmd_fjoined,     NULL},
  {"fleft",     "n",    (IntFunc) cmd_fleft,       NULL},
  {"fmsg",      "n",    (IntFunc) cmd_fmsg,        NULL},
  {NULL,        NULL,   NULL,                      NULL}
};

static char *fakebotnet_close()
{
  module_undepend(MODULE_NAME);
  rem_builtins(H_dcc, fakebotnet_dcc);
  return NULL;
}

static Function fakebotnet_table[] =
{
  (Function) fakebotnet_start,
  (Function) fakebotnet_close,
  (Function) fakebotnet_expmem,
  (Function) fakebotnet_report,
};

char *fakebotnet_start(Function *global_funcs)
{
  global = global_funcs;
  module_register(MODULE_NAME, fakebotnet_table, FAKEBOTNET_MAJORV, FAKEBOTNET_MINORV);
  if (!module_depend(MODULE_NAME, "eggdrop", 108, 4)) {
    module_undepend(MODULE_NAME);
    return "This module requires Eggdrop 1.8.4 or later.";
  }
  add_builtins(H_dcc, fakebotnet_dcc);
  return NULL;
}
