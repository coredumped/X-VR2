<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
  <meta http-equiv="content-type" content="text/html; charset=ISO-8859-1">
  <title>eSolutions4All Portable API</title>
</head>
<body>
<table width=100% height=100% border=0 cellspacing=0 cellpadding=0 rules=none frame=void>
<tr>
<td valign=top>
<?php
require_once("menu.php");
echo "</td></tr>\n<tr><td valign=top>\n";
switch($place){
	case 'coding':
		require_once("coding-conventions.php");
		break;
	case 'features':
		require_once("features.php");
		break;
	case 'about':
		require_once("about.php");
		break;
	case 'sqldriver-howto':
		print "\n\n\n\n<div align=center>NOT READY YET</div>\n\n\n\n";
		break;
	default:
		require_once("home.php");
}
?>
</td>
</tr>
</table>
</body>
</html>
