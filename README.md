ReggieBabelJungleBody
=====================

Mind mapping like a Purple Pikmin

Project Timeline
----------------

Iteration 1: 10/7 - 10/14
- Create graph structure (directed/undirected) debug mode for testing

Iteration 2: 10/14 - 10/28
- Saving and loading files
- OpenGL and GLUT GUI (differently shaped nodes for context)

Iteration 3: 10/28 - 10/31
- Topologically sort directed graphs (to make todo lists, etc.)

Stakeholder Review 1: 10/31

Iteration 4: 10/31 - 11/14
- Importing data automatically into graph form
- Multiple default templates (calendars, people, general/multi-purpose)

Iteration 5: 11/14 - 11/21
- Exporting graph data into outside software ( i.e. Google Calendar)

Stakeholder Review 2: 11/21


Supplemental Specifications
---------------------------

Must
- User must be able to use software on linux
- User must be able to save and load files
- User must be able to use templates when creating a new project
- Program must be built in c++ and use only standard libraries, OpenGL and GLUT
- User should be able to export projects into different file format

Should
- Program should function on hardware capable of running Ubuntu 13.04
- User should be able to create custom templates
- Bugs in software should be rare or nonexistent
- Program will not be installable, but will be standalone

Could
- Response time should be fast
- Graphics should appear aesthetically pleasing

Will Not
- Import text files into graph format


Work Breakdown Structure
------------------------
Create backend graph structure
- Allow creation of directed & undirected nodes
- Give a simple text-based interface

Implement Saving & loading
- Save as XML file
- Keep position & format of nodes in addition to connections

Create  graphics (OpenGL & GLUT GUI)
- GLUT GUI handles the program window
- OpenGL displays the nodes & connections

Write algorithm to topologically sort directed graphs
- States whether such a sort is possible
- Allows graph to be output as hierarchically indented text file

Enable addition of attachments for various data types:
- Audio (.wav, .mp3)
- Video (.mp4, .mov)
- Image (.jpg, .png)

Enable exporting graph data into outside software/data types:
- Calendars (.ics)
- PDF
- Images (.jpg, .png)

Create default templates and custom template builder
- Allows user to insert pre-made graph templates (Calendar, Timeline etc.)
- Allows user to create custom templates for future use
