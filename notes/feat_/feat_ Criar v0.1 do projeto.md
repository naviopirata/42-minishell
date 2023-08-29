---
status: Doing
due: 2023-08-15
merged: false
points:
tags:
  - 
type:
  - 
milestones:
---

- [ ] feat_ Criar v0.1 do projeto
	- [ ] task_ Criar uma estrutura de dados
	- [ ] task_ Criar parser para o comando Echo
	- [ ] task_ Criar o executor que chame Echo e retorne


```
cat echoed.txt > void.txt | sort < tail void.txt | grep pirate | cat void.txt
```


```mermaid
	flowchart TD
	readuser{User input?}
	err{Error?}
	c2(( ))
	
	
	START -->
	readuser -- yes --> err
	readuser -- no --> Read_Doc
	
	Read_Doc -->
	err

	err -- yes ------- RETURN
	err -- no --> 
	Make_AST -->
	Tokenize -->
	Execute ---
	c2
	
	c2 -->
	readuser
	
	RETURN
```

```mermaid
	flowchart TD
	hasOper{Has Operator?}
	ispipe{Is pipe?}
	c1(( ))
	

	EXECUTE -->
	hasOper
	

	Execute_Pipe ---
	c1
	
	Execute_Redirect ---
	c1
	
	Execute_Once ---
	c1

	c1 -->
	Free_AST -->
	RETURN


	subgraph Execute_AST
		hasOper -- yes -->
			Select_Operator	-->
			Exec_Operator -->
			ispipe -- yes --> Execute_Pipe
			ispipe -- no --> Execute_Redirect

		hasOper -- no -->
			Execute_Once
	end
```

```mermaid
	flowchart TD
	isChild{Is Child?}
	c1(( ))
	
	EXECUTE_ONCE -->
	Fork -->
	isChild -- yes --> Execve
	isChild -- no --- c1

	Execve ---
	c1 -->
	Wait -->
	RETURN
```


```mermaid
	flowchart TD
	c1(( ))
	ischild{Is Child?}
	isgrandchild{Is G child?}
	c2(( ))

	EXECUTE_PIPE -->
	Fork -->
	ischild -- yes --> Create_Pipedes
	ischild -- no --- c1

	Create_Pipedes -->
	Fork_Child -->
	isgrandchild -- yes --> Execute_Cmd_1
	isgrandchild -- no --- c2

	Execute_Cmd_1 ---
	c2 

	c2 -->
	Wait_GChild -->
	Execute_Cmd_2 ---
	c1

	c1 -->
	Wait -->	
	RETURN
```

```mermaid
	flowchart TD
	c1(( ))
	c2(( ))
	checkappend{Append?}
	ischild{Is Child?}

	EXECUTE_REDIRECT -->
	Fork -->
	ischild -- yes --> checkappend
	ischild -- no --- c1

	checkappend -- yes --> Open_FD_Append --- c2
	checkappend -- no --> Open_FD_Write_Only --- c2

	c2 -->
	Close_Extra_FD -->
	Dup -->
	Execute ---
	c1
	
	c1 -->
	Wait -->

	RETURN

```
