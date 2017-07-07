The task management program functions these basic operations
	1. Adding task,
	2. Editing Task
	3. Deleting Task
	4. Listing all Task

Running the program,
	
	Un the TaskMaagement.exe in the bin/Debug folder, and it will run the program.
	
Program Description:

The program runs in console window.
First the user will see a list of actions and the user has to pick a number for selecting that action.

	*To add a task, the user has to provide two information, the task name and task description
	*To edit a task, the user has to provide the task name. If the user gives the correct task name, the program will fetch a  table showing the previous
		information. The the user has to provide at least one information (Task Name/ Description) to edit the task detail. The user can skip giving information
		by pressing enter, when a input has been asked.
	*To delete a task, the user has to provide the task name. If the user gives the correct task name, the program will fetch a  table showing which row 
	has been deleted. The user can skip giving information by pressing enter, when a input has been asked.

	
Code description:
The program has been designed with MVC structure in mind. 
The code has 3 classes. 
	1. MainViewController
	2. Task
	3. View
	
"MainViewController" is the controller for this program. "Task" is the model file, it mainly interacts with the database and passes data to controller. 
The "View" operates as the view in MVC it only shows data and collects input and passes it to controller.


MainViewController has the following methods,
	1. showView
	2. addTaskVC
	3. editTaskVC
	4. deleteTaskVC
	5. tableVC
	6. _actionCB
	7. getTaskIdVC
	
	*"showView" is the entry point of the program, the main function in the Main.cpp calls this method. It calls the View method(showCommands) with 
		parameters. The "showCommands" method then shows option. And once the user has given an input, it calls the callback function, give by "showView"
	
	*"addTaskVC" shows user instruction via, "getTaskNameDescription" method in View. "getTaskNameDescription" also returns Task Name and Task Description
		from user. Then "addTaskVC" calls the "addItem" in Task. Once the insertion is complete. It shows success message.
		
	*"editTaskVC" gets a task name from "getTaskName" method in View. Then it fetches a row with "getRow" method in Task model. Then it gets name and description
		with "getTaskNameDescription" method in View. Then it updates information with "updateItem" method in Task.
		
	*"deleteTaskVC" gets a task name from "getTaskName" method in View. Then it fetches a row with "getRow" method in Task model. And then deletes the row 
		with "deleteItem" method in Task
		

		
External libraries:

Two external libraries has been used in this program.
	The first one is "Sqlite3" for managing database. 
	Another is BPrinter, this one is mainly used for formatting the table and to give it a nice design.
		
	