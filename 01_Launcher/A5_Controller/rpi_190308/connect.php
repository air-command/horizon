<?php
    if($_POST['connect']) {
        $gpio_connect = shell_exec("/usr/local/bin/gpio -g write 17 0");
    } else {
        $gpio_connect = shell_exec("/usr/local/bin/gpio -g write 17 1");
    }
?>
