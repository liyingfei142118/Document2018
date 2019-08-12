<?php
$str=trim(fgets(STDIN));//字符串输入
$str_arr=explode(" ",$str);//explode（）将字符串分割成了数组
$i=count($str_arr);//count（）计算数组的长度
$i--;
for(;$i>=0;$i--)
{
		echo $str_arr[$i];
	if($i!=0)
		echo " ";
}
?>