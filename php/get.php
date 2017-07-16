<?php

	$connection = mysql_connect("localhost","ame97software","");
	mysql_select_db("my_ame97software",$connection);
    
    $query="SELECT * FROM astar";
    
    $result=mysql_query($query,$connection);
    $row=mysql_fetch_array($result);
   if($_POST['value']==1)
   $row=mysql_fetch_array($result);  //prendi la seconda riga
   
    echo $row[1];
  
?>