---
status: Done
due: 2023-08-13
merged: false
effort: 0
tags:
type:
milestones:
---
***diagram - basic use of fork and execve functions***

```mermaid
	flowchart TD
	c1(( ))
	Wait["Wait pid1\n Wait pid2"]

	Start -->
	Read["Read user input"] -->
	Fork

	Wait -->
	Return
	subgraph Parent
		Fork --- c1
		Fork --> Child1
	
		Child1 --->
		Pipe -->
		Child2 ---
		c1 -->
		Wait
	end
	

	subgraph Child1
		Execcat["Exec cat test.txt"]
	end

	subgraph Child2
		Execgrep["grep pirate"]
	end

	subgraph Pipe
		dup2child1["Dup2 Child1"] -->
		pipew["Pipe Write"] -->
		stdout["STDOUT"] -->
		dup2child2["Dup2 Child2"] -->
		piper["Pipe Read"] -->
		stdin["STDIN"]
	end
```

```
	flowchart TD
	if{"True?"} 
	c1(( ))

	Start([Start]) -->
	write[Input data: ] -->
	Read -->

	if -- yes --> parse
	if -- no --> unload

	parse -. save .-> 
	database[(Database)]

	unload ==> 
	mem{{Memory}} ---
	c1 -->
	Return([Return])
```

```
	flowchart LR
	 
	 A --> TOP --> B

	  subgraph TOP
	    direction TB
	    	 B1 --> B2
	  end

	    subgraph B1
	        direction RL
	        i1 -->f1
	    end

	    subgraph B2
	        direction BT
	        i2 -->f2
	    end
```
