<?php
    $setmode17 = shell_exec("/usr/local/bin/gpio -g mode 17 out");      // connected
    $setmode27 = shell_exec("/usr/local/bin/gpio -g mode 27 out");      // launch
    $setmode22 = shell_exec("/usr/local/bin/gpio -g mode 22 out");      // fill
    $setmode10 = shell_exec("/usr/local/bin/gpio -g mode 10 out");      // vent
//	echo "in PHP init";
    $gpio_fill   = shell_exec("/usr/local/bin/gpio -g write 17 0");
    $gpio_vent   = shell_exec("/usr/local/bin/gpio -g write 22 1");
    $gpio_launch = shell_exec("/usr/local/bin/gpio -g write 27 1");
    $gpio_conn   = shell_exec("/usr/local/bin/gpio -g write 10 1");
?>
