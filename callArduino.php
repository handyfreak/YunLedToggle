<?php 

define ("USERNAME", "root");
define ("PASSWORD", "arduino");
define ("BASE_URL", "http://localhost/arduino/");

if(count($argv) != 2) printUsage();
else echo sendCommand($argv[1]);

function printUsage() {
	echo "Usage: callArduino.php <command>\n";
}

function sendCommand($command) {
	
	$fullURL = BASE_URL . $command;
	
	// inizialize the cURL library
	$ch = curl_init();
	curl_setopt($ch,CURLOPT_CONNECTTIMEOUT, 10);
	curl_setopt($ch,CURLOPT_RETURNTRANSFER, true);
	curl_setopt($ch,CURLOPT_TIMEOUT, 60);
	curl_setopt($ch, CURLOPT_USERPWD, USERNAME . ":" . PASSWORD);
	
	// set gateway URL and parameters
	curl_setopt($ch,CURLOPT_URL, $fullURL);
	
	// make the request and return the response
	$response = curl_exec($ch);
	curl_close($ch);
	return $response;
}

?>