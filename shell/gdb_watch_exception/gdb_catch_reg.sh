# 本文件负责catch handle的实现

# log 工具
# zsh下正常工作， bash 下有问题， 先不用了
#define log_line
#  set $i = 0
#  shell echo -e "[GDB_INFO] [\c"
#  shell echo -e `date '+%Y_%m_%d %H:%M:%S'`"\c"
#  shell echo -e "]  \c"
#  while $i < $argc
#    eval "set $log_temp_str = $arg%d", $i
#    printf "%s",$log_temp_str
#    set $i = $i + 1
#  end
#  printf "\n"
#end

define log_title
  shell echo -e "[GDB_INFO] [\c"
  shell echo -e `date '+%Y_%m_%d %H:%M:%S'`"\c"
  shell echo -e "]  \c"
  printf "%s%s%s\n",$arg1,$arg0,$arg1
end

# 打印断点处的详细数据
define print_stack
  set scheduler-locking on
  set $page_trace_gap_str = "\t!!!!!!!!!!!!!!!!!!!\t"
  set $content_trace_gap_str = "\t+++++++++++++++++\t"
  printf "\n\n"
  log_title "start print trace" $page_trace_gap_str
  log_title "print stack trace" $content_trace_gap_str
  bt
  log_title "print register" $content_trace_gap_str
  info r
  log_title "print local vars" $content_trace_gap_str
  info local
  log_title "print threads info" $content_trace_gap_str
  info threads
  log_title "print all thread break track" $content_trace_gap_str
  thread apply all bt
  log_title "end print trace" $page_trace_gap_str
  printf "\n\n"
  set scheduler-locking off
end

define reg_throw_handle
  catch throw
    commands
      print_stack
      continue
    end
  catch signal 6 8 11
    commands
      print_stack
      continue
    end
end
