ReggieBabelJungleBody
=====================

Mind mapping like a Purple Pikmin

Supplemental Specifications
---------------------------

<big>Must</big><br />
&middot;User must be able to use software on linux<br />
&middot;User must be able to save and load files<br />
&middot;User must be able to use templates when creating a new project<br />
&middot;Program must be built in c++ and use only standard libraries, OpenGL and GLUT<br />
&middot;User should be able to export projects into different file formats<br />

<big>Should</big><br />
&middot;Program should function on hardware capable of running Ubuntu 13.04<br />
&middot;User should be able to create custom templates<br />
&middot;Bugs in software should be rare or nonexistent<br />
&middot;Program will not be installable, but will be standalone<br />

<big>Could</big><br />
&middot;Response time should be fast<br />
&middot;Graphics should appear aesthetically pleasing<br />

<big>Will Not</big><br />
&middot;Import text files into graph format<br />


Work Breakdown Structure
------------------------
Create backend graph structure<br />
	* Allow creation of directed & undirected nodes<br />
	* Give a simple text-based interface<br />
Implement Saving & loading<br />
	* Save as XML file<br />
	* Keep position & format of nodes in addition to connections<br />
Create  graphics (OpenGL & GLUT GUI)<br />
	* GLUT GUI handles the program window<br />
	* OpenGL displays the nodes & connections<br />
Write algorithm to topologically sort directed graphs<br />
	* States whether such a sort is possible<br />
	* Allows graph to be output as hierarchically indented text file<br />
Enable addition of attachments for various data types:<br />
	* Audio (.wav, .mp3)<br />
	* Video (.mp4, .mov)<br />
	* Image (.jpg, .png)<br />
Enable exporting graph data into outside software/data types:<br />
	* Calendars (.ics)<br />
	* PDF<br />
	* Images (.jpg, .png)<br />
Create default templates and custom template builder<br />
	* Allows user to insert pre-made graph templates (Calendar, Timeline etc.)<br />
	* Allows user to create custom templates for future use<br />
