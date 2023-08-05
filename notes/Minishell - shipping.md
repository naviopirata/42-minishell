## Basic interaction


```mermaid
	sequenceDiagram
	autonumber

	participant User
	participant Shell

	loop
		alt
			User -->> Shell : Enter command
			Shell -->> Shell: Run command
			Shell -->> User : Return prompt
		end
		opt
			User -->> Shell : Send signal
			Shell -->> User : Handle signal
			Shell -->> User : Finish program
		end
	end

```

## Main structure

```mermaid
	flowchart TD

	Begin -->
	signals_init -->
	signal_terminate{TERM signal?} -- yes --> unload_mem
	signal_terminate{TERM signal?} -- no --> command_parse
	
	command_parse -->
	command_run -->
	Return

	unload_mem -->
	Return
```

**Parsing**

```mermaid
	flowchart TD
	c1(( ))
	c2(( ))

	command_parse -->
	has_pipe{Has pipes?} -- yes --> pipe_queue
	has_pipe{Has pipes?} -- no --> command_eval_1

	command_eval_1 -->
	command_isvalid_1{Command is valid?} -- yes --> command_run_1
	command_isvalid_1{Command is valid?} -- no --> error_raise_1

	pipe_queue -->
	cmd_loop{"Evaluate all\nqueue commands?"} -- yes --> all_good
	cmd_loop{"Evaluate all\nqueue commands?"} -- no --> cmd_loop
	
	all_good{All good?} -- yes --> command_run_queue
	all_good{All good?} -- no --> error_raise_2

	command_run_1 -->
	c1 
	
	error_raise_1 --> 
	c1 
	
	command_run_queue -->
	c2 
	
	error_raise_2 -->
	c2 
	
	c1 -->
	Return
	
	c2 -->
	Return
```

```mermaid
	flowchart TD

	command_run_queue -->
	command_run_1 -- pipe -->
	command_run_2 -- pipe -->
	command_run_n -->
	Return
```

### To Dos

- Built-ins
- Handle history


```mermaid
flowchart TD
start -->
read_line -->
get_string -->
parse_string -->
execute -->
return
```

// get_string -> echo "hi mom"
// parse_string -> cortar echo e hi mom
// exec -> fork/ pid/ stdout

