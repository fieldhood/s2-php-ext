<?php

var_dump(s2_cellid(31.31835, 121.63846));
$cellids = s2_getconver(31.31835, 121.63846, 2000.0, 256);
var_dump($cellids);
