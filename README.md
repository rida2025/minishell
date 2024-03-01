this project was done by mmxv and jessou
parsing guide:
first: create your structures
check the input of the command
if its null or contain only a empty strig
if null stop as its a ctrl+d
if its empty string dont insert it in histroy and just continue
other cases u split the input
before spliting and inserting check the syntax error of quotes from the string u got
if there is a sytanx error let the user know and continue
then split spaces outside quotes in there own node $ or | or quotes or < > << >> in there own node
now check sytanx error again of pipe and redirections
if there is a sytanx error let the user know and continue (back to readline !)
now exapnd
exapaning guide:
u dont exapand if there is $"" or $''
more in details soon.
