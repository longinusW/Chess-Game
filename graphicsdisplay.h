#ifndef _GRAPHICDISPLAY_H_
#define _GRAPHICDISPLAY_H_

#include "window.h"
#include "coor.h"
#include "info.h"
#include <cstddef>
#include <memory>
class GraphicsDisplay {
    std::unique_ptr<Xwindow> xw; // the Xwindow which is owned by the GraphicsDisplay class
    void draw_num(Coor coor);
    void draw_letter(Coor coor);
	public:
	void graphic_init(); // draw initialized grid window with size n
    	void normInit();
	void getNotify(Coor was, Coor des, Type t, Colour colour); // change pieces' colour on the window
};

#endif
