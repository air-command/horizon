<?php
    if($_POST['fill']) {
        $gpio_fill = shell_exec("/usr/local/bin/gpio -g write 22 0");
    } else {
        $gpio_fill = shell_exec("/usr/local/bin/gpio -g write 22 1");
    }

    if($_POST['vent']) {
        $gpio_vent = shell_exec("/usr/local/bin/gpio -g write 10 0");
    } else {
        $gpio_vent = shell_exec("/usr/local/bin/gpio -g write 10 1");
    }

    if($_POST['launch']) {
        $gpio_launch = shell_exec("/usr/local/bin/gpio -g write 27 0");
    } else {
        $gpio_launch = shell_exec("/usr/local/bin/gpio -g write 27 1");
    }
?>
