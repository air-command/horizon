<?php	
	$data = $_POST['photo'];
	$game = $_POST['game'];
	list($type, $data) = explode(';', $data);
	list(, $data)      = explode(',', $data);
	$data = base64_decode($data);

	file_put_contents("photo_".$game."_".time().'.png', $data);
	die;
?>