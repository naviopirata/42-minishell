# Anotações  
(17/08/2023 17:53:21)

# “PROCESS CREATION” (Kerrisk, 2018, p. 513)

- “z The fork() system call allows one process, the parent, to create a new process, the child.” (Kerrisk, 2018, p. 513)

- “This is done by making the new child process an (almost) exact duplicate of the parent: the child obtains copies of the parent’s stack, data, heap, and text segments” (Kerrisk, 2018, p. 513)

- “z The exit(status) library function terminates a process, making all resources (memory, open file descriptors, and so on) used by the process available for subsequent reallocation by the kernel.” (Kerrisk, 2018, p. 513)

- “The status argument is an integer that determines the termination status for the process. Using the wait() system call, the parent can retrieve this status.” (Kerrisk, 2018, p. 513)

- “The exit() library function is layered on top of the _exit() system call.” (Kerrisk, 2018, p. 514)

- “z The wait(&status) system call has two purposes. First, if a child of this process has not yet terminated by calling exit(), then wait() suspends execution of the process until one of its children has terminated.” (Kerrisk, 2018, p. 514)

- “Second, the termination status of the child is returned in the status argument of wait().” (Kerrisk, 2018, p. 514)

- “z The execve(pathname, argv, envp) system call loads a new program (pathname, with argument list argv, and environment list envp) into a process’s memory.” (Kerrisk, 2018, p. 514)

- “The existing program text is discarded, and the stack, data, and heap segments are freshly created for the new program.” (Kerrisk, 2018, p. 514)

- “Figure 24-1 provides an overview of how fork(), exit(), wait(), and execve() are commonly used together.” (Kerrisk, 2018, p. 514)

- “we’ll see later that the use of wait() is usually desirable, and is often employed within a handler for the SIGCHLD signal, which the kernel generates for a parent process when one of its children terminates.” (Kerrisk, 2018, p. 514)

![[Pasted image 20230820220458.png]]
## “24.2 Creating a New Process: fork()” (Kerrisk, 2018, p. 515)

- “The key point to understanding fork() is to realize that after it has completed its work, two processes exist, and, in each process, execution continues from the point where fork() returns.” (Kerrisk, 2018, p. 516)

- “The two processes are executing the same program text, but they have separate copies of the stack, data, and heap segments.” (Kerrisk, 2018, p. 516)

- “After the fork(), each process can modify the variables in its stack, data, and heap segments without affecting the other process.” (Kerrisk, 2018, p. 516)

- “For the child, fork() returns 0. If necessary, the child can obtain its own process ID using getpid(), and the process ID of its parent using getppid().” (Kerrisk, 2018, p. 516)

- “It is important to realize that after a fork(), it is indeterminate which of the two processes is next scheduled to use the CPU.” (Kerrisk, 2018, p. 516)

## “24.2.1 File Sharing Between Parent and Child” (Kerrisk, 2018, p. 517)

- “the child receives duplicates of all of the parent’s file descriptors. These duplicates are made in the manner of dup(), which means that corresponding descriptors in the parent and the child refer to the same open file description.” (Kerrisk, 2018, p. 517)

- “if the child updates the file offset, this change is visible through the corresponding descriptor in the parent.” (Kerrisk, 2018, p. 518)

![[Pasted image 20230820220649.png]]
## “24.2.2 Memory Semantics of fork()” (Kerrisk, 2018, p. 520)

![[Pasted image 20230820220719.png]] 

- “Controlling a process’s memory footprint” (Kerrisk, 2018, p. 521)

- “We can combine the use of fork() and wait() to control the memory footprint of a process.” (Kerrisk, 2018, p. 521)

- “The process’s memory footprint is the range of virtual memory pages used by the process,” (Kerrisk, 2018, p. 521)

## “24.4 Race Conditions After fork()” (Kerrisk, 2018, p. 525)

- “After a fork(), it is indeterminate which process—the parent or the child—next has access to the CPU.” (Kerrisk, 2018, p. 525)

# “PROCESS TERMINATION” (Kerrisk, 2018, p. 531)

## “25.1 Terminating a Process: _exit() and exit()” (Kerrisk, 2018, p. 531)

- “By convention, a termination status of 0 indicates that a process completed successfully, and a nonzero status value indicates that the process terminated” (Kerrisk, 2018, p. 531)

- “Programs generally don’t call _exit() directly, but instead call the exit() library function, which performs various actions before calling _exit().” (Kerrisk, 2018, p. 532)

- “The stdio stream buffers are flushed.” (Kerrisk, 2018, p. 532)

- “One other way in which a process may terminate is to return from main(), either explicitly, or implicitly, by falling off the end of the main() function.” (Kerrisk, 2018, p. 532)

- “Performing an explicit return n is generally equivalent to calling exit(n), since the run-time function that invokes main() uses the return value from main() in a call to exit().” (Kerrisk, 2018, p. 532)

- “Performing a return without specifying a value, or falling off the end of the main() function, also results in the caller of main() invoking exit(), but with results that vary depending on the version of the C standard supported and the compilation options employed” (Kerrisk, 2018, p. 532)

## “25.3 Exit Handlers” (Kerrisk, 2018, p. 533)

- “An exit handler is a programmer-supplied function that is registered at some point during the life of the process and is then automatically called during normal process termination via exit().” (Kerrisk, 2018, p. 534)

- “The first method, specified in SUSv3, is to use the atexit() function.” (Kerrisk, 2018, p. 534)

- “To address these limitations, glibc provides a (nonstandard) alternative method of registering exit handlers: on_exit().” (Kerrisk, 2018, p. 535)

## “25.4 Interactions Between fork(), stdio Buffers, and _exit()” (Kerrisk, 2018, p. 537)

- “o understand why the message written with printf() appears twice, recall that the stdio buffers are maintained in a process’s user-space memory” (Kerrisk, 2018, p. 538)

- “When the parent and the child later call exit(), they both flush their copies of the stdio buffers, resulting in duplicate output.” (Kerrisk, 2018, p. 538)

- “The output of the write() in the program in Listing 25-2 doesn’t appear twice, because write() transfers data directly to a kernel buffer, and this buffer is not duplicated during a fork().” (Kerrisk, 2018, p. 538)

- “The output of write() appears before that from printf() because the output of write() is immediately transferred to the kernel buffer cache, while the output from printf() is transferred only when the stdio buffers are flushed by the call to exit().” (Kerrisk, 2018, p. 538)

# “MONITORING CHILD PROCESSES” (Kerrisk, 2018, p. 541)

## “26.1 Waiting on a Child Process” (Kerrisk, 2018, p. 541)

- “In many applications where a parent creates child processes, it is useful for the parent to be able to monitor the children to find out when and how they terminate.” (Kerrisk, 2018, p. 541)

- “The wait() system call waits for one of the children of the calling process to terminate and returns the termination status of that child in the buffer pointed to by status.” (Kerrisk, 2018, p. 541)

- “1. If no (previously unwaited-for) child of the calling process has yet terminated, the call blocks until one of the children terminates.” (Kerrisk, 2018, p. 542)

- “2. If status is not NULL, information about how the child terminated is returned in the integer to which status points.” (Kerrisk, 2018, p. 542)

- “4. As its function result, wait() returns the process ID of the child that has terminated.” (Kerrisk, 2018, p. 542)

- “On error, wait() returns –1. One possible error is that the calling process has no (previously unwaited-for) children, which is indicated by the errno value ECHILD.” (Kerrisk, 2018, p. 542)


## “26.1.2 The waitpid() System Call” (Kerrisk, 2018, p. 544)

- “The wait() system call has a number of limitations, which waitpid() was designed to address:” (Kerrisk, 2018, p. 544)

- “z If a parent process has created multiple children, it is not possible to wait() for the completion of a specific child; we can only wait for the next child that terminates.” (Kerrisk, 2018, p. 544)

- “z If no child has yet terminated, wait() always blocks.” (Kerrisk, 2018, p. 544)

- “z Using wait(), we can find out only about children that have terminated.” (Kerrisk, 2018, p. 544)

- “The return value and status arguments of waitpid() are the same as for wait().” (Kerrisk, 2018, p. 544)

- “The pid argument enables the selection of the child to be waited for, as follows:” (Kerrisk, 2018, p. 544)

- “z If pid is greater than 0, wait for the child whose process ID equals pid.” (Kerrisk, 2018, p. 544)

- “z If pid equals 0, wait for any child in the same process group as the caller (parent).” (Kerrisk, 2018, p. 544)

- “z If pid is less than –1, wait for any child whose process group identifier equals the absolute value of pid.” (Kerrisk, 2018, p. 544)

- “z If pid equals –1, wait for any child. The call wait(&status) is equivalent to the call waitpid(–1, &status, 0).” (Kerrisk, 2018, p. 544)

- “The options argument is a bit mask that can include (OR) zero or more of the following flags” (Kerrisk, 2018, p. 544)

- “WUNTRACED” (Kerrisk, 2018, p. 544)

- “WCONTINUED” (Kerrisk, 2018, p. 544)

- “WNOHANG” (Kerrisk, 2018, p. 544)

## “26.1.3 The Wait Status Value” (Kerrisk, 2018, p. 545)

- “z The child terminated by calling _exit() (or exit()), specifying an integer exit status.” (Kerrisk, 2018, p. 545)

- “z The child was terminated by the delivery of an unhandled signal.” (Kerrisk, 2018, p. 545)

- “z The child was stopped by a signal, and waitpid() was called with the WUNTRACED flag.” (Kerrisk, 2018, p. 545)

- “z The child was resumed by a SIGCONT signal, and waitpid() was called with the WCONTINUED flag.” (Kerrisk, 2018, p. 545)

- “When applied to a status value returned by wait() or waitpid(), only one of the macros in the list below will return true.” (Kerrisk, 2018, p. 546)

![[Pasted image 20230820221242.png]]

- “WIFEXITED(status)” (Kerrisk, 2018, p. 546)

- “WIFSIGNALED(status)” (Kerrisk, 2018, p. 546)

- “WIFSTOPPED(status)” (Kerrisk, 2018, p. 546)

- “WIFCONTINUED(status)” (Kerrisk, 2018, p. 546)

## “26.1.4 Process Termination from a Signal Handler” (Kerrisk, 2018, p. 549)

- “some signals terminate a process by default. In some circumstances, we may wish to have certain cleanup steps performed before a process terminates.” (Kerrisk, 2018, p. 549)

- “For this purpose, we can arrange to have a handler catch such signals, perform the cleanup steps, and then terminate the process.” (Kerrisk, 2018, p. 549)

- “If the child needs to inform the parent that it terminated because of a signal, then the child’s signal handler should first disestablish itself, and then raise the” (Kerrisk, 2018, p. 549)

- “The signal handler would contain code such as the following:” (Kerrisk, 2018, p. 550)

## “26.1.6 The wait3() and wait4() System Calls” (Kerrisk, 2018, p. 552)

- “The wait3() and wait4() system calls perform a similar task to waitpid(). The principal semantic difference is that wait3() and wait4() return resource usage information about the terminated child in the structure pointed to by the rusage argument.” (Kerrisk, 2018, p. 552)

- “a call to wait3() is equivalent to the following waitpid() call: waitpid(-1, &status, options);” (Kerrisk, 2018, p. 552)

- “Similarly, wait4() is equivalent to the following: waitpid(pid, &status, options);” (Kerrisk, 2018, p. 552)

## “26.2 Orphans and Zombies” (Kerrisk, 2018, p. 553)

- “The lifetimes of parent and child processes are usually not the same—either the parent outlives the child or vice versa.” (Kerrisk, 2018, p. 553)

- “z Who becomes the parent of an orphaned child?” (Kerrisk, 2018, p. 553)

- “The orphaned child is adopted by init, the ancestor of all processes, whose process ID is 1.” (Kerrisk, 2018, p. 553)

- “z What happens to a child that terminates before its parent has had a chance to perform a wait()?” (Kerrisk, 2018, p. 553)

- “The kernel deals with this situation by turning the child into a zombie.” (Kerrisk, 2018, p. 553)

- “The only part of the process that remains is an entry in the kernel’s process table recording (among other things) the child’s process ID” (Kerrisk, 2018, p. 553)

- “When the parent does perform a wait(), the kernel removes the zombie, since the last remaining information about the child is no longer required.” (Kerrisk, 2018, p. 553)

- “On the other hand, if the parent terminates without doing a wait(), then the init process adopts the child and automatically performs a wait(), thus removing the zombie process from the system.” (Kerrisk, 2018, p. 553)

## “26.3 The SIGCHLD Signal” (Kerrisk, 2018, p. 555)

- “The termination of a child process is an event that occurs asynchronously. A parent can’t predict when one of its child will terminate.” (Kerrisk, 2018, p. 555)

- “z The parent can call wait(), or waitpid() without specifying the WNOHANG flag, in which case the call will block if a child has not already terminated.” (Kerrisk, 2018, p. 555)

- “z The parent can periodically perform a nonblocking check (a poll) for dead children via a call to waitpid() specifying the WNOHANG flag.” (Kerrisk, 2018, p. 555)

- “On the one hand, we may not want the parent to be blocked waiting for a child to terminate. On the other hand, making repeated nonblocking waitpid() calls wastes CPU time and adds complexity to an application design.” (Kerrisk, 2018, p. 555)

## “26.3.1 Establishing a Handler for SIGCHLD” (Kerrisk, 2018, p. 555)

- “The SIGCHLD signal is sent to a parent process whenever one of its children terminates. By default, this signal is ignored, but we can catch it by installing a signal handler.” (Kerrisk, 2018, p. 555)

- “The solution is to loop inside the SIGCHLD handler, repeatedly calling waitpid() with the WNOHANG flag until there are no more dead children to be reaped.” (Kerrisk, 2018, p. 556)

- “while (waitpid(-1, NULL, WNOHANG) > 0) continue;” (Kerrisk, 2018, p. 556)

- “Design issues for SIGCHLD handlers” (Kerrisk, 2018, p. 556)

- “A portable application can make this difference invisible by establishing the SIGCHLD handler before creating any children.” (Kerrisk, 2018, p. 556)

# “PROGRAM EXECUTION” (Kerrisk, 2018, p. 563)

## “27.1 Executing a New Program: execve()” (Kerrisk, 2018, p. 563)

- “The execve() system call loads a new program into a process’s memory.” (Kerrisk, 2018, p. 563)

- “the new program commences execution at its main() function.” (Kerrisk, 2018, p. 563)

- “The most frequent use of execve() is in the child produced by a fork()” (Kerrisk, 2018, p. 563)

- “Various library functions, all with names beginning with exec, are layered on top of the execve() system call. Each of these functions provides a different interface to the same functionality.” (Kerrisk, 2018, p. 563)

- “The pathname argument contains the pathname of the new program to be loaded into the process’s memory.” (Kerrisk, 2018, p. 564)

- “The argv argument specifies the command-line arguments to be passed to the new program.” (Kerrisk, 2018, p. 564)

- “it is a NULL-terminated list of pointers to character strings.” (Kerrisk, 2018, p. 564)

- “The value supplied for argv[0] corresponds to the command name. Typically, this value is the same as the basename” (Kerrisk, 2018, p. 564)

- “The envp argument corresponds to the environ array of the new program; it is a NULLterminated list of pointers” (Kerrisk, 2018, p. 564)

- “Since it replaces the program that called it, a successful execve() never returns.” (Kerrisk, 2018, p. 564)

- “we can use errno to determine the cause.” (Kerrisk, 2018, p. 564)

![[Pasted image 20230820221804.png]]

## “27.2.1 The PATH Environment Variable” (Kerrisk, 2018, p. 568)

- “The execvp() and execlp() functions allow us to specify just the name of the file to be executed.” (Kerrisk, 2018, p. 568)

- “These functions make use of the PATH environment variable to search for the file.” (Kerrisk, 2018, p. 568)

- “The PATH value for a login shell is set by system-wide and user-specific shell startup scripts.” (Kerrisk, 2018, p. 568)

- “Since a child process inherits a copy of its parent’s environment variables, each process that the shell creates to execute a command inherits a copy of the shell’s PATH.” (Kerrisk, 2018, p. 568)

## “27.3 Interpreter Scripts” (Kerrisk, 2018, p. 572)

- “An interpreter is a program that reads commands in text form and executes them.” (Kerrisk, 2018, p. 572)

- “First, execute permission” (Kerrisk, 2018, p. 572)

- “Second” (Kerrisk, 2018, p. 572)

- “interpreter” (Kerrisk, 2018, p. 572)

- “#! interpreter-path [ optional-arg ]” (Kerrisk, 2018, p. 572)

- “Execution of interpreter scripts” (Kerrisk, 2018, p. 573)

- “Since a script doesn’t contain binary machine code, when execve() is used to run the script” (Kerrisk, 2018, p. 573)

![[Pasted image 20230820222001.png]]

## “27.4 File Descriptors and exec()” (Kerrisk, 2018, p. 575)

- “By default, all file descriptors opened by a program that calls exec() remain open across the exec() and are available for use by the new program.” (Kerrisk, 2018, p. 575)

- “The shell takes advantage of this feature to handle I/O redirection for the programs that it executes” (Kerrisk, 2018, p. 575)

- “1. A fork() is performed to create a child process” (Kerrisk, 2018, p. 575)

- “2. The child shell opens dir.txt for output using file descriptor 1 (standard output).” (Kerrisk, 2018, p. 575)

- “Then, if that file descriptor is not standard output, the shell uses dup2() to force standard output to be a duplicate of the new descriptor and closes the new descriptor,” (Kerrisk, 2018, p. 575)

- “3. The child shell execs the ls program. The ls program writes its output to standard output, which is the file dir.txt.” (Kerrisk, 2018, p. 576)

- “In particular, certain commands—so-called shell built-in commands—are executed directly by the shell, without performing a fork() or an exec(). Such commands must be treated somewhat differently for the purposes of I/O redirection.” (Kerrisk, 2018, p. 576)

- “A shell command is implemented as a built-in for either of two reasons: efficiency and to obtain side effects within the shell.” (Kerrisk, 2018, p. 576)

- “Other commands are implemented within the shell so that they have side effects on the shell itself” (Kerrisk, 2018, p. 576)

- “For example, the cd command must change the working directory of the shell itself, and so can’t be executed within a separate process.” (Kerrisk, 2018, p. 576)

- “The close-on-exec flag (FD_CLOEXEC)” (Kerrisk, 2018, p. 576)

- “Sometimes, it may be desirable to ensure that certain file descriptors are closed before an exec().” (Kerrisk, 2018, p. 576)

- “then it is secure programming practice to ensure that all unnecessary file descriptors are closed before the new program is loaded.” (Kerrisk, 2018, p. 576)

- “If this flag is set, then the file descriptor is automatically closed during a successful exec(), but left open if the exec() fails.” (Kerrisk, 2018, p. 577)

- “When dup(), dup2(), or fcntl() is used to create a duplicate of a file descriptor, the close-on-exec flag is always cleared for the duplicate descriptor.” (Kerrisk, 2018, p. 577)

## “27.5 Signals and exec()” (Kerrisk, 2018, p. 578)

- “During an exec(), the text of the existing process is discarded. This text may include signal handlers established by the calling program.” (Kerrisk, 2018, p. 578)

- “Because the handlers disappear, the kernel resets the dispositions of all handled signals to SIG_DFL.” (Kerrisk, 2018, p. 578)

## “27.6 Executing a Shell Command: system()” (Kerrisk, 2018, p. 579)

## “27.7 Implementing system()” (Kerrisk, 2018, p. 582)

- “A simple implementation of system()” (Kerrisk, 2018, p. 582)

- “$ sh -c "ls | wc"” (Kerrisk, 2018, p. 582)

- “we need to use fork() to create a child that then does an execl() with arguments corresponding to the above sh command:” (Kerrisk, 2018, p. 582)

- “execl("/bin/sh", "sh", "-c", command, (char \*) NULL);” (Kerrisk, 2018, p. 582)

- “To collect the status of the child created by system(), we use a waitpid() call that specifies the child’s process ID.” (Kerrisk, 2018, p. 582)

- “Treating signals correctly inside system()” (Kerrisk, 2018, p. 583)

- “What adds complexity to the implementation of system() is the correct treatment with signals.” (Kerrisk, 2018, p. 583)

- “The first signal to consider is SIGCHLD.” (Kerrisk, 2018, p. 583)

- “when a SIGCHLD signal is generated by the termination of the child created by system(), it is possible that the signal handler of the main program will be invoked—and collect the child’s status—before system() has a chance to call waitpid().” (Kerrisk, 2018, p. 583)

- “Therefore, system() must block delivery of SIGCHLD while it is executing.” (Kerrisk, 2018, p. 583)

- “The other signals to consider are those generated by the terminal interrupt (usually Control-C) and quit (usually Control-\) characters, SIGINT and SIGQUIT, respectively.” (Kerrisk, 2018, p. 583)

- “Therefore, when we type the interrupt or quit characters, all three processes are sent the corresponding signal.” (Kerrisk, 2018, p. 583)

- “The shell ignores SIGINT and SIGQUIT while waiting for it” (Kerrisk, 2018, p. 583)

- “584 Chapter 27 child.” (Kerrisk, 2018, p. 584)

- “How should the calling process and the executed command respond to these signals?” (Kerrisk, 2018, p. 584)

- “z SIGINT and SIGQUIT should be ignored in the calling process while the command is being executed.” (Kerrisk, 2018, p. 584)

- “z In the child, SIGINT and SIGQUIT should be treated as they would be if the calling process did a fork() and exec(); that is, the disposition of handled signals is reset to the default, and the disposition of other signals remains unchanged.” (Kerrisk, 2018, p. 584)

- “While the command is being executed, typing Control-C or Control-\ will kill only the child of system(),” (Kerrisk, 2018, p. 584)

![[Pasted image 20230820224408.png]]

- “An improved system() implementation” (Kerrisk, 2018, p. 585)

- “z As noted earlier, if command is a NULL pointer, then system() should return nonzero if a shell is available or 0 if no shell is available.” (Kerrisk, 2018, p. 585)

- “z It is only in the parent process (the caller of system()) that SIGCHLD needs to be blocked w, and SIGINT and SIGQUIT need to be ignored e.” (Kerrisk, 2018, p. 585)

- “z In the parent, we ignore errors from the sigaction() and sigprocmask() calls used to manipulate signal dispositions and the signal mask w e o.” (Kerrisk, 2018, p. 585)

- “z Error checking is not performed for signal-related system calls in the child r t.” (Kerrisk, 2018, p. 585)

- “z On return from fork() in the child, the disposition of SIGINT and SIGQUIT is SIG_IGN (i.e., the disposition inherited from the parent).” (Kerrisk, 2018, p. 586)

- “z If the execl() call in the child fails, then we use _exit() to terminate the process y, rather than exit(), in order to prevent flushing of any unwritten data in the child’s copy of the stdio buffers.” (Kerrisk, 2018, p. 586)

- “z In the parent, we must use waitpid() to wait specifically for the child that we created u.” (Kerrisk, 2018, p. 586)

- “the calling program may have established signal handlers, and one of these could interrupt a blocked call to waitpid().” (Kerrisk, 2018, p. 586)

- “SUSv3 explicitly requires that the wait be restarted in this case. Therefore, we use a loop to restart waitpid() if it fails with the error EINTR u; any other error from waitpid() causes this loop to terminate.” (Kerrisk, 2018, p. 586)

- “Further details on system()” (Kerrisk, 2018, p. 588)

- “Portable applications should ensure that system() is not called with the disposition of SIGCHLD set to SIG_IGN, because it is impossible for the waitpid() call to obtain the status of the child in this case.” (Kerrisk, 2018, p. 588)

## “PIPES AND FIFOS” (Kerrisk, 2018, p. 889)

- “We can think of a pipe as a piece of plumbing that allows data to flow from one process to another.” (Kerrisk, 2018, p. 889)

- “the two processes are connected to the pipe so that the writing process (ls) has its standard output (file descriptor 1) joined to the write end of the pipe, while the reading process (wc) has its standard input (file descriptor 0) joined to the read end of the pipe.” (Kerrisk, 2018, p. 890)

- “In effect, these two processes are unaware of the existence of the pipe; they just read from and write to the standard file descriptors.” (Kerrisk, 2018, p. 890)

- “A pipe is a byte stream” (Kerrisk, 2018, p. 890)

- “we mean that there is no concept of messages or message boundaries when using a pipe.” (Kerrisk, 2018, p. 890)

- “The process reading from a pipe can read blocks of data of any size, regardless of the size of blocks written by the writing process.” (Kerrisk, 2018, p. 890)

- “Furthermore, the data passes through the pipe sequentiallybytes are read from a pipe in exactly the order they were written.” (Kerrisk, 2018, p. 890)

- “Reading from a pipe” (Kerrisk, 2018, p. 890)

- “Attempts to read from a pipe that is currently empty block until at least one byte has been written to the pipe.” (Kerrisk, 2018, p. 890)

- “If the write end of a pipe is closed, then a process reading from the pipe will see end-of-file (i.e., read() returns 0) once it has read all remaining data in the pipe.” (Kerrisk, 2018, p. 890)

- “Pipes are unidirectional” (Kerrisk, 2018, p. 890)

- “Data can travel only in one direction through a pipe. One end of the pipe is used for writing, and the other end is used for reading.” (Kerrisk, 2018, p. 890)

- “Writes of up to PIPE_BUF bytes are guaranteed to be atomic” (Kerrisk, 2018, p. 891)

- “If multiple processes are writing to a single pipe, then it is guaranteed that their data won’t be intermingled if they write no more than PIPE_BUF bytes at a time.” (Kerrisk, 2018, p. 891)

- “Pipes have a limited capacity” (Kerrisk, 2018, p. 891)

- “A pipe is simply a buffer maintained in kernel memory. This buffer has a maximum capacity. Once a pipe is full, further writes to the pipe block until the reader removes some data from the pipe.” (Kerrisk, 2018, p. 891)

## “44.2 Creating and Using Pipes” (Kerrisk, 2018, p. 892)

- “A successful call to pipe() returns two open file descriptors in the array filedes: one for the read end of the pipe ( filedes[0]) and one for the write end ( filedes[1]).” (Kerrisk, 2018, p. 892)

- “As with any file descriptor, we can use the read() and write() system calls to perform I/O on the pipe.” (Kerrisk, 2018, p. 892)

- “Once written to the write end of a pipe, data is immediately available to be read from the read end.” (Kerrisk, 2018, p. 892)

- “Normally, we use a pipe to allow communication between two processes.” (Kerrisk, 2018, p. 892)

- “To connect two processes using a pipe, we follow the pipe() call with a call to fork().” (Kerrisk, 2018, p. 892)

- “During a fork(), the child process inherits copies of its parent’s file descriptors” (Kerrisk, 2018, p. 892)

- “immediately after the fork(), one process closes its descriptor for the write end of the pipe, and the other closes its descriptor for the read end.” (Kerrisk, 2018, p. 893)

- “be sure which process will be the first to succeed—the two processes race for data.” (Kerrisk, 2018, p. 894)

- “Pipes allow communication between related processes” (Kerrisk, 2018, p. 894)

- “pipes can be used for communication between any two (or more) related processes, as long as the pipe was created by a common ancestor before the series of fork() calls that led to the existence of the processes.” (Kerrisk, 2018, p. 894)

- “For example, a pipe could be used for communication between a process and its grandchild.” (Kerrisk, 2018, p. 894)

- “A common scenario is that a pipe is used for communication between two siblings—their parent creates the pipe, and then creates the two children. This is what the shell does when building a pipeline.” (Kerrisk, 2018, p. 894)

- “Closing unused pipe file descriptors” (Kerrisk, 2018, p. 894)

- “If the reading process doesn’t close the write end of the pipe, then, after the other process closes its write descriptor, the reader won’t see end-of-file, even after” (Kerrisk, 2018, p. 894)

- “it has read all data from the pipe. Instead, a read() would block waiting for data, because the kernel knows that there is still at least one write descriptor open for the pipe.” (Kerrisk, 2018, p. 895)

- “When a process tries to write to a pipe for which no process has an open read descriptor, the kernel sends the SIGPIPE signal to the writing process.” (Kerrisk, 2018, p. 895)

- “the write() on the pipe fails with the error EPIPE (broken pipe).” (Kerrisk, 2018, p. 895)

## “44.3 Pipes as a Method of Process Synchronization” (Kerrisk, 2018, p. 897)

- “Furthermore, this technique could be extended so that, instead of closing the pipe, each child writes a message to the pipe containing its process ID and some status information.” (Kerrisk, 2018, p. 899)

## “44.4 Using Pipes to Connect Filters” (Kerrisk, 2018, p. 899)

- “two filters” (Kerrisk, 2018, p. 899)

- “are connected using a pipe, such that the standard output of one program is directed into the pipe and the standard input of the other is taken from the pipe?” (Kerrisk, 2018, p. 899)

- “duplicating file descriptors.” (Kerrisk, 2018, p. 899)

- “The end result of the above steps is that the process’s standard output is bound to the write end of the pipe.” (Kerrisk, 2018, p. 899)

- “A corresponding set of calls can be used to bind a process’s standard input to the read end of the pipe.” (Kerrisk, 2018, p. 899)

- “the following dup2() call, which allows us to explicitly specify the descriptor to be bound to the pipe end” (Kerrisk, 2018, p. 899)

- “dup2(pfd[1], STDOUT_FILENO);” (Kerrisk, 2018, p. 899)

## “44.5 Talking to a Shell Command via a Pipe: popen()” (Kerrisk, 2018, p. 902)

- “The popen() function creates a pipe, and then forks a child process that execs a shell, which in turn creates a child process to execute the string given in command.” (Kerrisk, 2018, p. 902)

- “The mode argument is a string that determines whether the calling process will read from the pipe (mode is r) or write to it (mode is w)” (Kerrisk, 2018, p. 902)

- “On success, popen() returns a file stream pointer that can be used with the stdio library functions.” (Kerrisk, 2018, p. 902)

- “then popen() returns NULL and sets errno to indicate the cause of the error.” (Kerrisk, 2018, p. 902)

- “After the popen() call, the calling process uses the pipe to read the output of command or to send input to it.” (Kerrisk, 2018, p. 902)

- “Using popen() offers convenience. It builds the pipe, performs descriptor duplication, closes unused descriptors, and handles all of the details of fork() and exec() on our behalf.” (Kerrisk, 2018, p. 903)

- “z Since the calling process and the executed command are operating in parallel, SUSv3 requires that popen() should not ignore SIGINT and SIGQUIT” (Kerrisk, 2018, p. 903)

- “z Since the calling process may create other child processes between the execution of popen() and pclose(), SUSv3 requires that popen() should not block SIGCHLD.” (Kerrisk, 2018, p. 903)

- “By contrast, if ls is given the name of a file that doesn’t exist, it prints an error message on stderr (which we dispose of by redirecting stderr to /dev/null), prints nothing on stdout, and exits with a status of 1.” (Kerrisk, 2018, p. 905)

## “44.6 Pipes and stdio Buffering” (Kerrisk, 2018, p. 906)

- “the stdio library applies block buffering to the file stream” (Kerrisk, 2018, p. 906)

- “we can either use periodic calls to fflush() or disable stdio buffering using the call setbuf(fp, NULL).” (Kerrisk, 2018, p. 906)

## “44.7 FIFOs” (Kerrisk, 2018, p. 906)

- “Semantically, a FIFO is similar to a pipe. The principal difference is that a FIFO has a name within the file system and is opened in the same way as a regular file.” (Kerrisk, 2018, p. 906)

## “44.10 Semantics of read() and write() on Pipes and FIFOs” (Kerrisk, 2018, p. 917)

- “The only difference between blocking and nonblocking reads occurs when no data is present and the write end is open.” (Kerrisk, 2018, p. 917)