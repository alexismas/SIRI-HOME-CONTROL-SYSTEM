<?php
		//echo exec('./writeaction '.$_GET["value"]);
		//echo " write value : ".$_GET["value"];
		$file = fopen("action.txt", "w");
		fwrite($file,$_GET["value"]);
		fclose($file);
?>