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

	Start -->
	Fork --- c1
	Fork --> Child

	Child ---
	c1 -->
	Wait -->
	Return

	subgraph Child
		Exec
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
