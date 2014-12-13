#include "ofpsvr.h"

mrb_value ofpsvr_uid(mrb_state *mrb, mrb_value obj)
{
  return mrb_fixnum_value(getuid());
}

mrb_value ofpsvr_gid(mrb_state *mrb, mrb_value obj)
{
  return mrb_fixnum_value(getgid());
}

mrb_value ofpsvr_halt(mrb_state *mrb, mrb_value obj)
{
  return mrb_fixnum_value(raise(SIGINT));
}
