// AUTOGENERATED FILE

struct call_t {
	const char*	name;
	int		sys_nr;
};

// Note: this is x86_64 number
#ifndef __NR_getrandom
#define __NR_getrandom 318
#endif
#ifndef __NR_memfd_create
#define __NR_memfd_create 319
#endif
#ifndef __NR_bpf
#define __NR_bpf 321
#endif
#ifndef __NR_userfaultfd
#define __NR_userfaultfd 323
#endif
#ifndef __NR_membarrier
#define __NR_membarrier 324
#endif
#ifndef __NR_mlock2
#define __NR_mlock2 325
#endif

#define __NR_syz_openpts	1000001
#define __NR_syz_dri_open	1000002
#define __NR_syz_fuse_mount	1000003
#define __NR_syz_fuseblk_mount	1000004

call_t syscalls[] = {
	{"open", __NR_open},
	{"openat", __NR_openat},
	{"creat", __NR_creat},
	{"close", __NR_close},
	{"read", __NR_read},
	{"pread64", __NR_pread64},
	{"readv", __NR_readv},
	{"preadv", __NR_preadv},
	{"write", __NR_write},
	{"pwrite64", __NR_pwrite64},
	{"writev", __NR_writev},
	{"pwritev", __NR_pwritev},
	{"lseek", __NR_lseek},
	{"dup", __NR_dup},
	{"dup2", __NR_dup2},
	{"dup3", __NR_dup3},
	{"pipe", __NR_pipe},
	{"pipe2", __NR_pipe2},
	{"tee", __NR_tee},
	{"splice", __NR_splice},
	{"vmsplice", __NR_vmsplice},
	{"sendfile", __NR_sendfile},
	{"stat", __NR_stat},
	{"lstat", __NR_lstat},
	{"fstat", __NR_fstat},
	{"poll", __NR_poll},
	{"ppoll", __NR_ppoll},
	{"select", __NR_select},
	{"pselect6", __NR_pselect6},
	{"epoll_create", __NR_epoll_create},
	{"epoll_create1", __NR_epoll_create1},
	{"epoll_ctl", __NR_epoll_ctl},
	{"epoll_wait", __NR_epoll_wait},
	{"epoll_pwait", __NR_epoll_pwait},
	{"signalfd", __NR_signalfd},
	{"signalfd4", __NR_signalfd4},
	{"eventfd", __NR_eventfd},
	{"eventfd2", __NR_eventfd2},
	{"timerfd_create", __NR_timerfd_create},
	{"timerfd_settime", __NR_timerfd_settime},
	{"timerfd_gettime", __NR_timerfd_gettime},
	{"userfaultfd", __NR_userfaultfd},
	{"ioctl$UFFDIO_API", __NR_ioctl},
	{"ioctl$UFFDIO_REGISTER", __NR_ioctl},
	{"ioctl$UFFDIO_UNREGISTER", __NR_ioctl},
	{"ioctl$UFFDIO_WAKE", __NR_ioctl},
	{"ioctl$UFFDIO_COPY", __NR_ioctl},
	{"ioctl$UFFDIO_ZEROPAGE", __NR_ioctl},
	{"mmap", __NR_mmap},
	{"munmap", __NR_munmap},
	{"mremap", __NR_mremap},
	{"remap_file_pages", __NR_remap_file_pages},
	{"mprotect", __NR_mprotect},
	{"msync", __NR_msync},
	{"madvise", __NR_madvise},
	{"fadvise64", __NR_fadvise64},
	{"readahead", __NR_readahead},
	{"mbind", __NR_mbind},
	{"move_pages", __NR_move_pages},
	{"migrate_pages", __NR_migrate_pages},
	{"set_mempolicy", __NR_set_mempolicy},
	{"get_mempolicy", __NR_get_mempolicy},
	{"mincore", __NR_mincore},
	{"mlock", __NR_mlock},
	{"mlock2", __NR_mlock2},
	{"munlock", __NR_munlock},
	{"mlockall", __NR_mlockall},
	{"munlockall", __NR_munlockall},
	{"memfd_create", __NR_memfd_create},
	{"unshare", __NR_unshare},
	{"kcmp", __NR_kcmp},
	{"futex", __NR_futex},
	{"set_robust_list", __NR_set_robust_list},
	{"get_robust_list", __NR_get_robust_list},
	{"restart_syscall", __NR_restart_syscall},
	{"socket", __NR_socket},
	{"socketpair", __NR_socketpair},
	{"accept", __NR_accept},
	{"accept4", __NR_accept4},
	{"bind", __NR_bind},
	{"listen", __NR_listen},
	{"connect", __NR_connect},
	{"shutdown", __NR_shutdown},
	{"sendto", __NR_sendto},
	{"sendmsg", __NR_sendmsg},
	{"sendmmsg", __NR_sendmmsg},
	{"recvfrom", __NR_recvfrom},
	{"recvmsg", __NR_recvmsg},
	{"recvmmsg", __NR_recvmmsg},
	{"getsockname", __NR_getsockname},
	{"getpeername", __NR_getpeername},
	{"getsockopt", __NR_getsockopt},
	{"setsockopt", __NR_setsockopt},
	{"getsockopt$sock_int", __NR_getsockopt},
	{"setsockopt$sock_int", __NR_setsockopt},
	{"getsockopt$sock_str", __NR_getsockopt},
	{"setsockopt$sock_str", __NR_setsockopt},
	{"getsockopt$sock_linger", __NR_getsockopt},
	{"setsockopt$sock_linger", __NR_setsockopt},
	{"getsockopt$sock_cred", __NR_getsockopt},
	{"setsockopt$sock_cred", __NR_setsockopt},
	{"getsockopt$sock_timeval", __NR_getsockopt},
	{"setsockopt$sock_timeval", __NR_setsockopt},
	{"setsockopt$sock_attach_bpf", __NR_setsockopt},
	{"getsockopt$tcp_int", __NR_getsockopt},
	{"setsockopt$tcp_int", __NR_setsockopt},
	{"getsockopt$tcp_buf", __NR_getsockopt},
	{"setsockopt$tcp_buf", __NR_setsockopt},
	{"getsockopt$udp_int", __NR_getsockopt},
	{"setsockopt$udp_int", __NR_setsockopt},
	{"getsockopt$ip_int", __NR_getsockopt},
	{"setsockopt$ip_int", __NR_setsockopt},
	{"getsockopt$ip_mreq", __NR_getsockopt},
	{"setsockopt$ip_mreq", __NR_setsockopt},
	{"getsockopt$ip_mreqn", __NR_getsockopt},
	{"setsockopt$ip_mreqn", __NR_setsockopt},
	{"getsockopt$ip_mreqsrc", __NR_getsockopt},
	{"setsockopt$ip_mreqsrc", __NR_setsockopt},
	{"getsockopt$ip_msfilter", __NR_getsockopt},
	{"setsockopt$ip_msfilter", __NR_setsockopt},
	{"getsockopt$ip_mtu", __NR_getsockopt},
	{"setsockopt$ip_mtu", __NR_setsockopt},
	{"getsockopt$ip_opts", __NR_getsockopt},
	{"setsockopt$ip_opts", __NR_setsockopt},
	{"getsockopt$ip_pktinfo", __NR_getsockopt},
	{"setsockopt$ip_pktinfo", __NR_setsockopt},
	{"getsockopt$ip_ipsec", __NR_getsockopt},
	{"setsockopt$ip_ipsec", __NR_setsockopt},
	{"getsockopt$ipv6_int", __NR_getsockopt},
	{"setsockopt$ipv6_int", __NR_setsockopt},
	{"getsockopt$ipv6_mreq", __NR_getsockopt},
	{"setsockopt$ipv6_mreq", __NR_setsockopt},
	{"getsockopt$ipv6_mtu", __NR_getsockopt},
	{"setsockopt$ipv6_mtu", __NR_setsockopt},
	{"getsockopt$ipv6_opts", __NR_getsockopt},
	{"setsockopt$ipv6_opts", __NR_setsockopt},
	{"ioctl", __NR_ioctl},
	{"ioctl$void", __NR_ioctl},
	{"ioctl$int_in", __NR_ioctl},
	{"ioctl$int_out", __NR_ioctl},
	{"ioctl$fiemap", __NR_ioctl},
	{"fcntl$dupfd", __NR_fcntl},
	{"fcntl$getflags", __NR_fcntl},
	{"fcntl$setflags", __NR_fcntl},
	{"fcntl$setstatus", __NR_fcntl},
	{"fcntl$lock", __NR_fcntl},
	{"fcntl$getown", __NR_fcntl},
	{"fcntl$setown", __NR_fcntl},
	{"fcntl$getownex", __NR_fcntl},
	{"fcntl$setownex", __NR_fcntl},
	{"fcntl$setsig", __NR_fcntl},
	{"fcntl$setlease", __NR_fcntl},
	{"fcntl$notify", __NR_fcntl},
	{"fcntl$setpipe", __NR_fcntl},
	{"fcntl$addseals", __NR_fcntl},
	{"ptrace", __NR_ptrace},
	{"ptrace$peek", __NR_ptrace},
	{"ptrace$poke", __NR_ptrace},
	{"ptrace$peekuser", __NR_ptrace},
	{"ptrace$pokeuser", __NR_ptrace},
	{"ptrace$getregs", __NR_ptrace},
	{"ptrace$getregset", __NR_ptrace},
	{"ptrace$setregs", __NR_ptrace},
	{"ptrace$setregset", __NR_ptrace},
	{"ptrace$getsig", __NR_ptrace},
	{"ptrace$setsig", __NR_ptrace},
	{"ptrace$setopts", __NR_ptrace},
	{"ptrace$getenv", __NR_ptrace},
	{"ptrace$cont", __NR_ptrace},
	{"io_setup", __NR_io_setup},
	{"io_destroy", __NR_io_destroy},
	{"io_getevents", __NR_io_getevents},
	{"io_submit", __NR_io_submit},
	{"io_cancel", __NR_io_cancel},
	{"capget", __NR_capget},
	{"capset", __NR_capset},
	{"prctl$void", __NR_prctl},
	{"prctl$intptr", __NR_prctl},
	{"prctl$getreaper", __NR_prctl},
	{"prctl$setendian", __NR_prctl},
	{"prctl$setfpexc", __NR_prctl},
	{"prctl$setname", __NR_prctl},
	{"prctl$getname", __NR_prctl},
	{"prctl$setptracer", __NR_prctl},
	{"prctl$seccomp", __NR_prctl},
	{"prctl$setmm", __NR_prctl},
	{"arch_prctl", __NR_arch_prctl},
	{"seccomp", __NR_seccomp},
	{"add_key", __NR_add_key},
	{"request_key", __NR_request_key},
	{"keyctl$get_keyring_id", __NR_keyctl},
	{"keyctl$join", __NR_keyctl},
	{"keyctl$update", __NR_keyctl},
	{"keyctl$revoke", __NR_keyctl},
	{"keyctl$describe", __NR_keyctl},
	{"keyctl$clear", __NR_keyctl},
	{"keyctl$link", __NR_keyctl},
	{"keyctl$unlink", __NR_keyctl},
	{"keyctl$search", __NR_keyctl},
	{"keyctl$read", __NR_keyctl},
	{"keyctl$chown", __NR_keyctl},
	{"keyctl$setperm", __NR_keyctl},
	{"keyctl$instantiate", __NR_keyctl},
	{"keyctl$negate", __NR_keyctl},
	{"keyctl$set_reqkey_keyring", __NR_keyctl},
	{"keyctl$set_timeout", __NR_keyctl},
	{"keyctl$assume_authority", __NR_keyctl},
	{"keyctl$get_security", __NR_keyctl},
	{"keyctl$session_to_parent", __NR_keyctl},
	{"keyctl$reject", __NR_keyctl},
	{"keyctl$instantiate_iov", __NR_keyctl},
	{"keyctl$invalidate", __NR_keyctl},
	{"keyctl$get_persistent", __NR_keyctl},
	{"mq_open", __NR_mq_open},
	{"mq_timedsend", __NR_mq_timedsend},
	{"mq_timedreceive", __NR_mq_timedreceive},
	{"mq_notify", __NR_mq_notify},
	{"mq_getsetattr", __NR_mq_getsetattr},
	{"mq_unlink", __NR_mq_unlink},
	{"msgget", __NR_msgget},
	{"msgsnd", __NR_msgsnd},
	{"msgrcv", __NR_msgrcv},
	{"msgctl", __NR_msgctl},
	{"semget", __NR_semget},
	{"semop", __NR_semop},
	{"semtimedop", __NR_semtimedop},
	{"semctl", __NR_semctl},
	{"shmget", __NR_shmget},
	{"shmat", __NR_shmat},
	{"shmctl", __NR_shmctl},
	{"shmdt", __NR_shmdt},
	{"mknod", __NR_mknod},
	{"mknodat", __NR_mknodat},
	{"chmod", __NR_chmod},
	{"fchmod", __NR_fchmod},
	{"fchmodat", __NR_fchmodat},
	{"chown", __NR_chown},
	{"lchown", __NR_lchown},
	{"fchown", __NR_fchown},
	{"fchownat", __NR_fchownat},
	{"fallocate", __NR_fallocate},
	{"faccessat", __NR_faccessat},
	{"utime", __NR_utime},
	{"utimes", __NR_utimes},
	{"futimesat", __NR_futimesat},
	{"utimensat", __NR_utimensat},
	{"getgid", __NR_getgid},
	{"getegid", __NR_getegid},
	{"setuid", __NR_setuid},
	{"setgid", __NR_setgid},
	{"getuid", __NR_getuid},
	{"geteuid", __NR_geteuid},
	{"setpgid", __NR_setpgid},
	{"getpgid", __NR_getpgid},
	{"getpgrp", __NR_getpgrp},
	{"getpid", __NR_getpid},
	{"gettid", __NR_gettid},
	{"setreuid", __NR_setreuid},
	{"setregid", __NR_setregid},
	{"setresuid", __NR_setresuid},
	{"setresgid", __NR_setresgid},
	{"getresuid", __NR_getresuid},
	{"getresgid", __NR_getresgid},
	{"setfsuid", __NR_setfsuid},
	{"setfsgid", __NR_setfsgid},
	{"getgroups", __NR_getgroups},
	{"setgroups", __NR_setgroups},
	{"personality", __NR_personality},
	{"inotify_init", __NR_inotify_init},
	{"inotify_init1", __NR_inotify_init1},
	{"inotify_add_watch", __NR_inotify_add_watch},
	{"inotify_rm_watch", __NR_inotify_rm_watch},
	{"fanotify_init", __NR_fanotify_init},
	{"fanotify_mark", __NR_fanotify_mark},
	{"link", __NR_link},
	{"linkat", __NR_linkat},
	{"symlinkat", __NR_symlinkat},
	{"symlink", __NR_symlink},
	{"unlink", __NR_unlink},
	{"unlinkat", __NR_unlinkat},
	{"readlink", __NR_readlink},
	{"readlinkat", __NR_readlinkat},
	{"rename", __NR_rename},
	{"renameat", __NR_renameat},
	{"renameat2", __NR_renameat2},
	{"mkdir", __NR_mkdir},
	{"mkdirat", __NR_mkdirat},
	{"rmdir", __NR_rmdir},
	{"truncate", __NR_truncate},
	{"ftruncate", __NR_ftruncate},
	{"flock", __NR_flock},
	{"fsync", __NR_fsync},
	{"fdatasync", __NR_fdatasync},
	{"sync", __NR_sync},
	{"syncfs", __NR_syncfs},
	{"sync_file_range", __NR_sync_file_range},
	{"lookup_dcookie", __NR_lookup_dcookie},
	{"getdents", __NR_getdents},
	{"getdents64", __NR_getdents64},
	{"name_to_handle_at", __NR_name_to_handle_at},
	{"open_by_handle_at", __NR_open_by_handle_at},
	{"mount", __NR_mount},
	{"mount$fs", __NR_mount},
	{"umount2", __NR_umount2},
	{"pivot_root", __NR_pivot_root},
	{"sysfs$1", __NR_sysfs},
	{"sysfs$2", __NR_sysfs},
	{"sysfs$3", __NR_sysfs},
	{"statfs", __NR_statfs},
	{"fstatfs", __NR_fstatfs},
	{"uselib", __NR_uselib},
	{"init_module", __NR_init_module},
	{"finit_module", __NR_finit_module},
	{"delete_module", __NR_delete_module},
	{"kexec_load", __NR_kexec_load},
	{"get_kernel_syms", __NR_get_kernel_syms},
	{"syslog", __NR_syslog},
	{"uname", __NR_uname},
	{"sysinfo", __NR_sysinfo},
	{"ustat", __NR_ustat},
	{"acct", __NR_acct},
	{"getrusage", __NR_getrusage},
	{"getrlimit", __NR_getrlimit},
	{"setrlimit", __NR_setrlimit},
	{"prlimit64", __NR_prlimit64},
	{"iopl", __NR_iopl},
	{"ioperm", __NR_ioperm},
	{"ioprio_get$pid", __NR_ioprio_get},
	{"ioprio_get$uid", __NR_ioprio_get},
	{"ioprio_set$pid", __NR_ioprio_set},
	{"ioprio_set$uid", __NR_ioprio_set},
	{"setns", __NR_setns},
	{"setxattr", __NR_setxattr},
	{"lsetxattr", __NR_lsetxattr},
	{"fsetxattr", __NR_fsetxattr},
	{"getxattr", __NR_getxattr},
	{"lgetxattr", __NR_lgetxattr},
	{"fgetxattr", __NR_fgetxattr},
	{"listxattr", __NR_listxattr},
	{"llistxattr", __NR_llistxattr},
	{"flistxattr", __NR_flistxattr},
	{"removexattr", __NR_removexattr},
	{"lremovexattr", __NR_lremovexattr},
	{"fremovexattr", __NR_fremovexattr},
	{"time", __NR_time},
	{"clock_gettime", __NR_clock_gettime},
	{"clock_settime", __NR_clock_settime},
	{"clock_adjtime", __NR_clock_adjtime},
	{"clock_getres", __NR_clock_getres},
	{"clock_nanosleep", __NR_clock_nanosleep},
	{"timer_create", __NR_timer_create},
	{"timer_gettime", __NR_timer_gettime},
	{"timer_getoverrun", __NR_timer_getoverrun},
	{"timer_settime", __NR_timer_settime},
	{"timer_delete", __NR_timer_delete},
	{"rt_sigaction", __NR_rt_sigaction},
	{"rt_sigprocmask", __NR_rt_sigprocmask},
	{"rt_sigreturn", __NR_rt_sigreturn},
	{"rt_sigpending", __NR_rt_sigpending},
	{"rt_sigtimedwait", __NR_rt_sigtimedwait},
	{"rt_sigsuspend", __NR_rt_sigsuspend},
	{"rt_sigqueueinfo", __NR_rt_sigqueueinfo},
	{"rt_tgsigqueueinfo", __NR_rt_tgsigqueueinfo},
	{"sigaltstack", __NR_sigaltstack},
	{"tgkill", __NR_tgkill},
	{"tkill", __NR_tkill},
	{"pause", __NR_pause},
	{"alarm", __NR_alarm},
	{"nanosleep", __NR_nanosleep},
	{"getitimer", __NR_getitimer},
	{"setitimer", __NR_setitimer},
	{"exit", __NR_exit},
	{"exit_group", __NR_exit_group},
	{"waitid", __NR_waitid},
	{"wait4", __NR_wait4},
	{"times", __NR_times},
	{"set_thread_area", __NR_set_thread_area},
	{"get_thread_area", __NR_get_thread_area},
	{"modify_ldt$read", __NR_modify_ldt},
	{"modify_ldt$write", __NR_modify_ldt},
	{"modify_ldt$read_default", __NR_modify_ldt},
	{"modify_ldt$write2", __NR_modify_ldt},
	{"process_vm_readv", __NR_process_vm_readv},
	{"process_vm_writev", __NR_process_vm_writev},
	{"set_tid_address", __NR_set_tid_address},
	{"getpriority", __NR_getpriority},
	{"setpriority", __NR_setpriority},
	{"sched_getscheduler", __NR_sched_getscheduler},
	{"sched_setscheduler", __NR_sched_setscheduler},
	{"sched_rr_get_interval", __NR_sched_rr_get_interval},
	{"sched_getparam", __NR_sched_getparam},
	{"sched_setparam", __NR_sched_setparam},
	{"sched_getaffinity", __NR_sched_getaffinity},
	{"sched_setaffinity", __NR_sched_setaffinity},
	{"sched_getattr", __NR_sched_getattr},
	{"sched_setattr", __NR_sched_setattr},
	{"sched_yield", __NR_sched_yield},
	{"getrandom", __NR_getrandom},
	{"membarrier", __NR_membarrier},
	{"ioctl$kdbus_bus_make", __NR_ioctl},
	{"ioctl$kdbus_ep_make", __NR_ioctl},
	{"ioctl$kdbus_ep_update", __NR_ioctl},
	{"ioctl$kdbus_hello", __NR_ioctl},
	{"ioctl$kdbus_name_acquire", __NR_ioctl},
	{"ioctl$kdbus_name_release", __NR_ioctl},
	{"ioctl$kdbus_free", __NR_ioctl},
	{"ioctl$kdbus_recv", __NR_ioctl},
	{"ioctl$kdbus_send", __NR_ioctl},
	{"ioctl$kdbus_update", __NR_ioctl},
	{"ioctl$kdbus_bye", __NR_ioctl},
	{"ioctl$kdbus_conn_info", __NR_ioctl},
	{"ioctl$kdbus_bus_info", __NR_ioctl},
	{"ioctl$kdbus_list", __NR_ioctl},
	{"ioctl$kdbus_match_add", __NR_ioctl},
	{"ioctl$kdbus_match_remove", __NR_ioctl},
	{"open$ptmx", __NR_open},
	{"syz_openpts", __NR_syz_openpts},
	{"ioctl$TCGETS", __NR_ioctl},
	{"ioctl$TCSETS", __NR_ioctl},
	{"ioctl$TCSETSW", __NR_ioctl},
	{"ioctl$TCSETSF", __NR_ioctl},
	{"ioctl$TCGETA", __NR_ioctl},
	{"ioctl$TCSETA", __NR_ioctl},
	{"ioctl$TCSETAW", __NR_ioctl},
	{"ioctl$TCSETAF", __NR_ioctl},
	{"ioctl$TIOCGLCKTRMIOS", __NR_ioctl},
	{"ioctl$TIOCSLCKTRMIOS", __NR_ioctl},
	{"ioctl$TIOCGWINSZ", __NR_ioctl},
	{"ioctl$TIOCSWINSZ", __NR_ioctl},
	{"ioctl$TCSBRK", __NR_ioctl},
	{"ioctl$TCSBRKP", __NR_ioctl},
	{"ioctl$TIOCSBRK", __NR_ioctl},
	{"ioctl$TIOCCBRK", __NR_ioctl},
	{"ioctl$TCXONC", __NR_ioctl},
	{"ioctl$FIONREAD", __NR_ioctl},
	{"ioctl$TIOCOUTQ", __NR_ioctl},
	{"ioctl$TCFLSH", __NR_ioctl},
	{"ioctl$TIOCSTI", __NR_ioctl},
	{"ioctl$TIOCCONS", __NR_ioctl},
	{"ioctl$TIOCSCTTY", __NR_ioctl},
	{"ioctl$TIOCNOTTY", __NR_ioctl},
	{"ioctl$TIOCGPGRP", __NR_ioctl},
	{"ioctl$TIOCSPGRP", __NR_ioctl},
	{"ioctl$TIOCGSID", __NR_ioctl},
	{"ioctl$TIOCEXCL", __NR_ioctl},
	{"ioctl$TIOCNXCL", __NR_ioctl},
	{"ioctl$TIOCGETD", __NR_ioctl},
	{"ioctl$TIOCSETD", __NR_ioctl},
	{"ioctl$TIOCPKT", __NR_ioctl},
	{"ioctl$TIOCMGET", __NR_ioctl},
	{"ioctl$TIOCMSET", __NR_ioctl},
	{"ioctl$TIOCMBIC", __NR_ioctl},
	{"ioctl$TIOCMBIS", __NR_ioctl},
	{"ioctl$TIOCGSOFTCAR", __NR_ioctl},
	{"ioctl$TIOCSSOFTCAR", __NR_ioctl},
	{"ioctl$TIOCTTYGSTRUCT", __NR_ioctl},
	{"ioctl$KDGETLED", __NR_ioctl},
	{"ioctl$KDSETLED", __NR_ioctl},
	{"ioctl$KDGKBLED", __NR_ioctl},
	{"ioctl$KDSKBLED", __NR_ioctl},
	{"ioctl$KDGKBTYPE", __NR_ioctl},
	{"ioctl$KDADDIO", __NR_ioctl},
	{"ioctl$KDDELIO", __NR_ioctl},
	{"ioctl$KDENABIO", __NR_ioctl},
	{"ioctl$KDDISABIO", __NR_ioctl},
	{"ioctl$KDSETMODE", __NR_ioctl},
	{"ioctl$KDGETMODE", __NR_ioctl},
	{"ioctl$KDMKTONE", __NR_ioctl},
	{"ioctl$KIOCSOUND", __NR_ioctl},
	{"ioctl$GIO_CMAP", __NR_ioctl},
	{"ioctl$PIO_CMAP", __NR_ioctl},
	{"ioctl$GIO_FONT", __NR_ioctl},
	{"ioctl$GIO_FONTX", __NR_ioctl},
	{"ioctl$PIO_FONT", __NR_ioctl},
	{"ioctl$PIO_FONTX", __NR_ioctl},
	{"ioctl$PIO_FONTRESET", __NR_ioctl},
	{"ioctl$GIO_SCRNMAP", __NR_ioctl},
	{"ioctl$GIO_UNISCRNMAP", __NR_ioctl},
	{"ioctl$PIO_SCRNMAP", __NR_ioctl},
	{"ioctl$PIO_UNISCRNMAP", __NR_ioctl},
	{"ioctl$GIO_UNIMAP", __NR_ioctl},
	{"ioctl$PIO_UNIMAP", __NR_ioctl},
	{"ioctl$PIO_UNIMAPCLR", __NR_ioctl},
	{"ioctl$KDGKBMODE", __NR_ioctl},
	{"ioctl$KDSKBMODE", __NR_ioctl},
	{"ioctl$KDGKBMETA", __NR_ioctl},
	{"ioctl$KDSKBMETA", __NR_ioctl},
	{"ioctl$KDGKBENT", __NR_ioctl},
	{"ioctl$KDGKBSENT", __NR_ioctl},
	{"ioctl$KDSKBSENT", __NR_ioctl},
	{"ioctl$KDGKBDIACR", __NR_ioctl},
	{"ioctl$KDGETKEYCODE", __NR_ioctl},
	{"ioctl$KDSETKEYCODE", __NR_ioctl},
	{"ioctl$KDSIGACCEPT", __NR_ioctl},
	{"ioctl$VT_OPENQRY", __NR_ioctl},
	{"ioctl$VT_GETMODE", __NR_ioctl},
	{"ioctl$VT_SETMODE", __NR_ioctl},
	{"ioctl$VT_GETSTATE", __NR_ioctl},
	{"ioctl$VT_RELDISP", __NR_ioctl},
	{"ioctl$VT_ACTIVATE", __NR_ioctl},
	{"ioctl$VT_WAITACTIVE", __NR_ioctl},
	{"ioctl$VT_DISALLOCATE", __NR_ioctl},
	{"ioctl$VT_RESIZE", __NR_ioctl},
	{"ioctl$VT_RESIZEX", __NR_ioctl},
	{"ioctl$TIOCLINUX2", __NR_ioctl},
	{"ioctl$TIOCLINUX3", __NR_ioctl},
	{"ioctl$TIOCLINUX4", __NR_ioctl},
	{"ioctl$TIOCLINUX5", __NR_ioctl},
	{"ioctl$TIOCLINUX6", __NR_ioctl},
	{"ioctl$TIOCLINUX7", __NR_ioctl},
	{"syz_dri_open", __NR_syz_dri_open},
	{"ioctl$DRM_IOCTL_VERSION", __NR_ioctl},
	{"ioctl$DRM_IOCTL_GET_UNIQUE", __NR_ioctl},
	{"ioctl$DRM_IOCTL_GET_MAGIC", __NR_ioctl},
	{"ioctl$DRM_IOCTL_IRQ_BUSID", __NR_ioctl},
	{"ioctl$DRM_IOCTL_GET_MAP", __NR_ioctl},
	{"ioctl$DRM_IOCTL_GET_CLIENT", __NR_ioctl},
	{"ioctl$DRM_IOCTL_GET_STATS", __NR_ioctl},
	{"ioctl$DRM_IOCTL_GET_CAP", __NR_ioctl},
	{"ioctl$DRM_IOCTL_SET_CLIENT_CAP", __NR_ioctl},
	{"ioctl$DRM_IOCTL_SET_VERSION", __NR_ioctl},
	{"syz_fuse_mount", __NR_syz_fuse_mount},
	{"syz_fuseblk_mount", __NR_syz_fuseblk_mount},
	{"ioctl$FUSE_DEV_IOC_CLONE", __NR_ioctl},
	{"write$fuse_init", __NR_write},
	{"write$fuse_interrupt", __NR_write},
	{"write$fuse_bmap", __NR_write},
	{"write$fuse_ioctl", __NR_write},
	{"write$fuse_poll", __NR_write},
	{"write$fuse_notify_poll_wakeup", __NR_write},
	{"write$fuse_notify_inval_inode", __NR_write},
	{"write$fuse_notify_inval_entry", __NR_write},
	{"write$fuse_notify_delete", __NR_write},
	{"write$fuse_notify_store", __NR_write},
	{"write$fuse_notify_retrieve", __NR_write},
	{"bpf$MAP_CREATE", __NR_bpf},
	{"bpf$MAP_LOOKUP_ELEM", __NR_bpf},
	{"bpf$MAP_UPDATE_ELEM", __NR_bpf},
	{"bpf$MAP_DELETE_ELEM", __NR_bpf},
	{"bpf$MAP_GET_NEXT_KEY", __NR_bpf},
	{"bpf$PROG_LOAD", __NR_bpf},
	{"bpf$OBJ_PIN_MAP", __NR_bpf},
	{"bpf$OBJ_PIN_PROG", __NR_bpf},
	{"bpf$OBJ_GET_MAP", __NR_bpf},
	{"bpf$OBJ_GET_PROG", __NR_bpf},
	{"perf_event_open", __NR_perf_event_open},
	{"ioctl$PERF_EVENT_IOC_ENABLE", __NR_ioctl},
	{"ioctl$PERF_EVENT_IOC_DISABLE", __NR_ioctl},
	{"ioctl$PERF_EVENT_IOC_RESET", __NR_ioctl},
	{"ioctl$PERF_EVENT_IOC_REFRESH", __NR_ioctl},
	{"ioctl$PERF_EVENT_IOC_PERIOD", __NR_ioctl},
	{"ioctl$PERF_EVENT_IOC_ID", __NR_ioctl},
	{"ioctl$PERF_EVENT_IOC_SET_OUTPUT", __NR_ioctl},
	{"ioctl$PERF_EVENT_IOC_SET_FILTER", __NR_ioctl},
	{"ioctl$PERF_EVENT_IOC_SET_BPF", __NR_ioctl},
	{"socket$alg", __NR_socket},
	{"bind$alg", __NR_bind},
	{"setsockopt$ALG_SET_KEY", __NR_setsockopt},
	{"setsockopt$ALG_SET_AEAD_AUTHSIZE", __NR_setsockopt},
	{"accept$alg", __NR_accept},
	{"sendmsg$alg", __NR_sendmsg},
	{"sendmmsg$alg", __NR_sendmmsg},
	{"recvmsg$alg", __NR_recvmsg},
	{"recvmmsg$alg", __NR_recvmmsg},
	{"socket$nfc_llcp", __NR_socket},
	{"bind$nfc_llcp", __NR_bind},
	{"connect$nfc_llcp", __NR_connect},
	{"accept$nfc_llcp", __NR_accept},
	{"setsockopt$NFC_LLCP_RW", __NR_setsockopt},
	{"setsockopt$NFC_LLCP_MIUX", __NR_setsockopt},
	{"getsockopt$nfc_llcp", __NR_getsockopt},
	{"sendmsg$nfc_llcp", __NR_sendmsg},
	{"sendmmsg$nfc_llcp", __NR_sendmmsg},
	{"socket$nfc_raw", __NR_socket},
	{"connect$nfc_raw", __NR_connect},
	{"socket$bt_hci", __NR_socket},
	{"bind$bt_hci", __NR_bind},
	{"ioctl$bt_hci", __NR_ioctl},
	{"setsockopt$HCI_DATA_DIR", __NR_setsockopt},
	{"setsockopt$HCI_TIME_STAMP", __NR_setsockopt},
	{"setsockopt$HCI_FILTER", __NR_setsockopt},
	{"getsockopt$bt_hci", __NR_getsockopt},
	{"socket$bt_sco", __NR_socket},
	{"bind$bt_sco", __NR_bind},
	{"connect$bt_sco", __NR_connect},
	{"getsockopt$SCO_OPTIONS", __NR_getsockopt},
	{"getsockopt$SCO_CONNINFO", __NR_getsockopt},
	{"socket$bt_l2cap", __NR_socket},
	{"bind$bt_l2cap", __NR_bind},
	{"connect$bt_l2cap", __NR_connect},
	{"setsockopt$L2CAP_OPTIONS", __NR_setsockopt},
	{"getsockopt$L2CAP_OPTIONS", __NR_getsockopt},
	{"setsockopt$L2CAP_LM", __NR_setsockopt},
	{"getsockopt$L2CAP_LM", __NR_getsockopt},
	{"setsockopt$L2CAP_CONNINFO", __NR_setsockopt},
	{"getsockopt$L2CAP_CONNINFO", __NR_getsockopt},
	{"socket$bt_rfcomm", __NR_socket},
	{"bind$bt_rfcomm", __NR_bind},
	{"connect$bt_rfcomm", __NR_connect},
	{"setsockopt$RFCOMM_LM", __NR_setsockopt},
	{"getsockopt$RFCOMM_LM", __NR_getsockopt},
	{"getsockopt$RFCOMM_CONNINFO", __NR_getsockopt},
	{"socket$bt_hidp", __NR_socket},
	{"ioctl$HIDPCONNADD", __NR_ioctl},
	{"ioctl$HIDPCONNDEL", __NR_ioctl},
	{"ioctl$HIDPGETCONNLIST", __NR_ioctl},
	{"ioctl$HIDPGETCONNINFO", __NR_ioctl},
	{"socket$bt_cmtp", __NR_socket},
	{"ioctl$CMTPCONNADD", __NR_ioctl},
	{"ioctl$CMTPCONNDEL", __NR_ioctl},
	{"ioctl$CMTPGETCONNLIST", __NR_ioctl},
	{"ioctl$CMTPGETCONNINFO", __NR_ioctl},
	{"socket$bt_bnep", __NR_socket},
	{"ioctl$BNEPCONNADD", __NR_ioctl},
	{"ioctl$BNEPCONNDEL", __NR_ioctl},
	{"ioctl$BNEPGETCONNLIST", __NR_ioctl},
	{"ioctl$BNEPGETCONNINFO", __NR_ioctl},
	{"ioctl$BNEPGETSUPPFEAT", __NR_ioctl},
	{"ioctl$bt", __NR_ioctl},
	{"setsockopt$BT_SECURITY", __NR_setsockopt},
	{"getsockopt$BT_SECURITY", __NR_getsockopt},
	{"setsockopt$BT_DEFER_SETUP", __NR_setsockopt},
	{"getsockopt$BT_DEFER_SETUP", __NR_getsockopt},
	{"setsockopt$BT_VOICE", __NR_setsockopt},
	{"getsockopt$BT_VOICE", __NR_getsockopt},
	{"setsockopt$BT_FLUSHABLE", __NR_setsockopt},
	{"getsockopt$BT_FLUSHABLE", __NR_getsockopt},
	{"setsockopt$BT_POWER", __NR_setsockopt},
	{"getsockopt$BT_POWER", __NR_getsockopt},
	{"setsockopt$BT_CHANNEL_POLICY", __NR_setsockopt},
	{"getsockopt$BT_CHANNEL_POLICY", __NR_getsockopt},
	{"setsockopt$BT_SNDMTU", __NR_setsockopt},
	{"getsockopt$BT_SNDMTU", __NR_getsockopt},
	{"setsockopt$BT_RCVMTU", __NR_setsockopt},
	{"getsockopt$BT_RCVMTU", __NR_getsockopt},
};
