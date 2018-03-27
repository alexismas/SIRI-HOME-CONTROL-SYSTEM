<?php
	

	echo exec('./gpioled'.$_GET["gpio"].' '.$_GET["value"]);
	
	

?>