<big><big><big><span style="font-weight: bold;">xvr2&acute;s Coding
Conventions</span></big></big></big><br>
<hr noshade="noshade"
 style="height: 2px; width: 100%; margin-left: 0px; margin-right: auto;"><br>
Before you start adding or modifying code on this library please take
special attention to the following rules:<br>
<table cellpadding="2" cellspacing="2" border="0"
 style="width: 100%; text-align: left;">
  <tbody>
    <tr>
      <td
 style="vertical-align: top; text-align: right; font-weight: bold;">1.<br>
      </td>
      <td style="vertical-align: top;">Class names must start with an <span
 style="font-weight: bold;">uppercase</span> character, if the name is
composed of many other small words, then each word must start with an
uppercase character. <br>
      </td>
    </tr>
    <tr>
      <td
 style="vertical-align: top; text-align: right; font-weight: bold;">2.<br>
      </td>
      <td style="vertical-align: top;">Variable names must be
completely underscore.<br>
      </td>
    </tr>
    <tr>
      <td
 style="vertical-align: top; text-align: right; font-weight: bold;">3.<br>
      </td>
      <td style="vertical-align: top;">If the name of a method is a
composed word, then the first word must be full lowercase, and the next
word should start with an uppercase character, if there is another word
then that word must have its first letter as an uppercase too.<br>
      </td>
    </tr>
    <tr>
      <td
 style="vertical-align: top; text-align: right; font-weight: bold;">4.<br>
      </td>
      <td style="vertical-align: top;">Every new class must be
contained in the namespace <span style="font-weight: bold;">xvr2</span><br>
      </td>
    </tr>
    <tr>
      <td
 style="vertical-align: top; text-align: right; font-weight: bold;">5.<br>
      </td>
      <td style="vertical-align: top;">Every class must be defined in a
source header, but must be implemented in a .cpp file. (do not use any
other file extension please)<br>
      </td>
    </tr>
    <tr>
      <td
 style="vertical-align: top; text-align: right; font-weight: bold;">6.<br>
      </td>
      <td style="vertical-align: top;">Every header file must use the
.h extension, not .H or .hpp<br>
      </td>
    </tr>
    <tr>
      <td
 style="vertical-align: top; text-align: right; font-weight: bold;">7.<br>
      </td>
      <td style="vertical-align: top;">Document every new class or
method you create, while documenting use the /** and */ tags.<br>
      </td>
    </tr>
    <tr>
      <td
 style="vertical-align: top; text-align: right; font-weight: bold;">8.<br>
      </td>
      <td style="vertical-align: top;">Everytime you can code a test
example for a class please feel free to do it<br>
      </td>
    </tr>
    <tr>
      <td
 style="vertical-align: top; text-align: right; font-weight: bold;">9.<br>
      </td>
      <td style="vertical-align: top;">If you want to create a new
class use the <span style="font-weight: bold;">createClass.sh</span>
script which is located under the src/wizards directory.<br>
      </td>
    </tr>
    <tr>
      <td
 style="vertical-align: top; text-align: right; font-weight: bold;">10.<br>
      </td>
      <td style="vertical-align: top;">If you need to create a new
class manually and/or do not wish to use the <span
 style="font-weight: bold;">createClass.sh</span> script please follow
this steps:<br>
      <table cellpadding="2" cellspacing="2" border="1" frame="border"
 style="background-color: silver; width: 100%; text-align: left;"
 rules="none">
        <tbody>
          <tr>
            <td style="vertical-align: top; text-align: right;">1.<br>
            </td>
            <td style="vertical-align: top;">Create the definition on a
.h header file.</td>
          </tr>
          <tr>
            <td style="vertical-align: top; text-align: right;">2.<br>
            </td>
            <td style="vertical-align: top;">Create your implementation
on a .cpp source file.</td>
          </tr>
          <tr>
            <td style="vertical-align: top; text-align: right;">3.<br>
            </td>
            <td style="vertical-align: top;">Create a static reference
to a class name using the <span style="font-weight: bold;">addClass.sh</span>
script.</td>
          </tr>
          <tr>
            <td style="vertical-align: top; text-align: right;">4.<br>
            </td>
            <td style="vertical-align: top;">In the constructor code
call the method <span style="font-weight: bold;">setClassName();</span>
and give the class name as a static reference.</td>
          </tr>
        </tbody>
      </table>
      </td>
    </tr>
    <tr>
      <td style="vertical-align: top; font-weight: bold;">11.<br>
      </td>
      <td style="vertical-align: top;">To create a new exception please
use the <span style="font-weight: bold;">addException.sh</span> script.<br>
      </td>
    </tr>
    <tr>
      <td style="vertical-align: top; font-weight: bold;">12.<br>
      </td>
      <td style="vertical-align: top;">If you need to create an
exception manually please follow this steps:<br>
      <table cellpadding="2" cellspacing="2" border="1"
 style="background-color: rgb(204, 204, 204); width: 100%; text-align: left;"
 rules="none" frame="border">
        <tbody>
          <tr>
            <td style="vertical-align: top; text-align: right;">1.<br>
            </td>
            <td style="vertical-align: top;">Use the <span
 style="font-weight: bold;">addClass.sh</span> script to create a static
string to hold its name</td>
          </tr>
          <tr>
            <td style="vertical-align: top; text-align: right;">2.<br>
            </td>
            <td style="vertical-align: top;">Use the <span
 style="font-weight: bold;">addMessageString.sh</span> script to create
a static string which will reference your exception description.</td>
          </tr>
          <tr>
            <td style="vertical-align: top; text-align: right;">3.<br>
            </td>
            <td style="vertical-align: top;">Edit <span
 style="font-weight: bold;">Exception.h</span> to create your exception
class definition, please take special care to select its parent class,
every new exception <span style="font-weight: bold;">must</span> has a
parent class.</td>
          </tr>
          <tr>
            <td style="vertical-align: top; text-align: right;">4.<br>
            </td>
            <td style="vertical-align: top;">Edit <span
 style="font-weight: bold;">Exception.cpp</span> in the constructor
allways call the <span style="font-weight: bold;">setClassName(); </span>method
and assign the description you created with the <span
 style="font-weight: bold;">addMessageString.sh</span> script.</td>
          </tr>
        </tbody>
      </table>
      </td>
    </tr>
    <tr>
      <td style="vertical-align: top; font-weight: bold;">13.<br>
      </td>
      <td style="vertical-align: top;">Try to use <span
 style="font-weight: bold;">const</span> as much as you can.<br>
      </td>
    </tr>
    <tr>
      <td style="vertical-align: top; font-weight: bold;">14.<br>
      </td>
      <td style="vertical-align: top;">If you detect a memory leak and
now how to clean it, please help us a little and do so.<br>
      </td>
    </tr>
    <tr>
      <td style="vertical-align: top; font-weight: bold;">15.<br>
      </td>
      <td style="vertical-align: top;">Please try not to exceed the
standard 80 characters in lenght for every source file.<br>
      </td>
    </tr>
    <tr>
      <td style="vertical-align: top; font-weight: bold;">16.<br>
      </td>
      <td style="vertical-align: top;">Indent using tabs for every
nested statement.<br>
      </td>
    </tr>
    <tr>
      <td style="vertical-align: top; font-weight: bold;">17.<br>
      </td>
      <td style="vertical-align: top;">Allways use <span
 style="font-weight: bold;">xvr2_delete();</span> and <span
 style="font-weight: bold;">xvr2_delete_array();</span> instead of the <span
 style="font-weight: bold;">delete();</span> operator.<br>
      </td>
    </tr>
    <tr>
      <td style="vertical-align: top; font-weight: bold;">18.<br>
      </td>
      <td style="vertical-align: top;">Try as much as you can not to
commit any code that can break the compilation process<br>
      </td>
    </tr>
    <tr>
      <td style="vertical-align: top; font-weight: bold;">19.<br>
      </td>
      <td style="vertical-align: top;">If you see typos (orthographical
errors) in people writings try to correct it yourself, but first notify
that you are going to do so.<br>
      </td>
    </tr>
    <tr>
      <td style="vertical-align: top; font-weight: bold;">20.<br>
      </td>
      <td style="vertical-align: top;">If you find code using low
performance algorithms feel free to provide new ones, but first try to
notify people that you are going to do so.<br>
      </td>
    </tr>
  </tbody>
</table>
