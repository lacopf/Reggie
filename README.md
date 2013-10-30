ReggieBabelJungleBody
=====================

Mind mapping like a Purple Pikmin

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
