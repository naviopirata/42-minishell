---
status: Backlog-80
due: 2023-08-06
merged: false
points:
tags:
  - 
type:
  - draw
milestones:
---
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

```mermaid
	flowchart TD
	pipesCount["Pipes count"]
	envUser["Env User"]
	envSys["Env System"]

	START -->
	Signal -->
	Lexer -->
	Parser -->
	Expander -->
	Executor <-->
	Return


	subgraph Lexer
		direction LR
		Command -->
		Order -->
		pipesCount
	end

	subgraph Parser
		direction LR
		quote[Quotes] -->
		backslash[Backslash]		
	end

	subgraph Expander
		direction LR
		envUser -->
		envSys
	end

	subgraph Executor
		direction LR
		Exec
	end
```