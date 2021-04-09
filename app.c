#include <janet.h>
#include <string.h>

int
run_some_janet ()
{
  JanetTable *env;

  janet_init ();

  env = janet_core_env (NULL);

  const char *embed = "(import ./entry :as app) (app/main 1)";

  janet_dostring (env, embed, "main", NULL);
  janet_deinit();

  return 0;
}

int
main (int argc, char *argv[])
{
  JanetTable *env;

  janet_init ();

  env = janet_core_env (NULL);

  // const char *embed = "(import ./scripts/app :as app) (app/main 1)";
  const char *embed = "(import ./entry :as app) (app/main 1)";

  janet_dostring (env, embed, "main", NULL);
  janet_deinit();

  return 0;
}
