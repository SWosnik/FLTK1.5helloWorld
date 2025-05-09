#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Table.H>
#include <FL/fl_draw.H>

#define MAX_ROWS 30
#define MAX_COLS 4

typedef struct
{
  int     lfnr;
  time_t  time;
  double  value;
} data_t;

// Derive a class from Fl_Table
class ResultTableView : public Fl_Table {

  data_t data[MAX_ROWS];		// data array for cells
  double min_value = 10.0;
  double max_value = 20.0;
  int data_index = 0;
  int next_lfnr = 1;

  // Draw the row/col headings
  //    Make this a dark thin upbox with the text inside.
  //
  void DrawHeader(const char *s, int X, int Y, int W, int H) {
    fl_push_clip(X,Y,W,H);
      fl_draw_box(FL_THIN_UP_BOX, X,Y,W,H, row_header_color());
      fl_color(FL_BLACK);
      fl_draw(s, X,Y,W,H, FL_ALIGN_CENTER);
    fl_pop_clip();
  }
  // Draw the cell data
  //    Dark gray text on white background with subtle border
  //
  void DrawData(const char *s, int X, int Y, int W, int H, int pass) {
    fl_push_clip(X,Y,W,H);
      // Draw cell bg
      if( pass )
      {
        fl_color(FL_WHITE);
        fl_rectf(X,Y,W,H);
      }
      else
      {
        fl_color(FL_RED);
        fl_rectf(X,Y,W,H);
      }
      // Draw cell data
      fl_color(FL_GRAY0); fl_draw(s, X,Y,W,H, FL_ALIGN_CENTER);
      // Draw box border
      fl_color(color()); fl_rect(X,Y,W,H);
    fl_pop_clip();
  }
  // Handle drawing table's cells
  //     Fl_Table calls this function to draw each visible cell in the table.
  //     It's up to us to use FLTK's drawing functions to draw the cells the way we want.
  //
  void draw_cell(TableContext context, int ROW=0, int COL=0, int X=0, int Y=0, int W=0, int H=0) {
    static char s[40];
    int pass = 1;

    switch ( context ) {
      case CONTEXT_STARTPAGE:                   // before page is drawn..
        fl_font(FL_HELVETICA, 16);              // set the font for our drawing operations
        return;
      case CONTEXT_COL_HEADER:                  // Draw column headers
        DrawHeader(TableHeadings[COL],X,Y,W,H);
        return;
      case CONTEXT_ROW_HEADER:                  // Draw row headers
        sprintf(s,"%03d:",ROW);                 // "001:", "002:", etc
        DrawHeader(s,X,Y,W,H);
        return;
      case CONTEXT_CELL:                        // Draw data in cells
      {
        s[0] = 0;
        if( ROW < data_index )
        {
          if( min_value > data[ROW].value || max_value < data[ROW].value )
            pass=0;
          switch(COL)
          {
          case 0 :
            sprintf(s,"%d",data[ROW].lfnr);
            break;
          case 1 :
            strftime(s, sizeof(s),"%H:%M:%S",localtime(&data[ROW].time));
            break;
          case 2 :
            sprintf(s,"%lf", data[ROW].value);
            break;
          case 3 :
            if( pass )
              sprintf(s,"PASS");
            else
              sprintf(s,"FAIL");
            break;
          }
        }
        DrawData(s,X,Y,W,H,pass);
        return;
      }
      default:
        return;
    }
  }

public:
  // Constructor
  //     Make our data array, and initialize the table options.
  //
  ResultTableView(int X, int Y, int W, int H, const char *L=0) : Fl_Table(X,Y,W,H,L) {
    // Fill data array
    data_index = 0;
    next_lfnr = 1;
    rows(MAX_ROWS);             // how many rows
    row_header(0);              // disable row headers ()
    row_height_all(20);         // default height of rows
    row_resize(0);              // disable row resizing
    // Cols
    cols(MAX_COLS);             // how many columns
    col_header(1);              // enable column headers (along top)
    col_width_all(100);          // default width of columns
    col_resize(1);              // enable column resizing
    end();			// end the Fl_Table group
  }
  ~ResultTableView() { }


  void setMinValue(double set_value) {
    min_value = set_value;
  }

  void setMaxValue(double set_value) {
    max_value = set_value;
  }

  double getMinValue( void ) {
    return min_value;
  }

  double getMaxValue( void ) {
    return max_value;
  }

void addValue(double set_value) {
    data[data_index].lfnr = next_lfnr;
    data[data_index].time = time(NULL);
    data[data_index].value = set_value;
    data_index++;
    next_lfnr++;
  }


private:
  const char* const TableHeadings[MAX_COLS] = { "LFNR", "Time", "Value", "Pass/Fail" };
};

// Callback function that gets triggered when the close-button is clicked
void closeCallback(Fl_Widget* widget, void*) {
    // Close the main window, which will terminate the application
    Fl_Window* win = (Fl_Window*)widget->window();
    win->hide();  // Hiding the window triggers FLTK's cleanup
}

// Callback function that gets triggered when the test-button is clicked
void testCallback(Fl_Widget* widget, void*) {
  //controller get next value
}

int main(int argc, char **argv) {
    // Create the main window
    Fl_Double_Window win(900, 450, "Simple Table");
    ResultTableView table(10,10,880,380);
    table.setMinValue(10.0);
    table.setMaxValue(1234.0);
    table.addValue(1.234567);
    table.addValue(12.34567);
    table.addValue(123.4567);
    table.addValue(1234.567);

    // Create a button labeled "test"
    Fl_Button *btn1 = new Fl_Button(20, 410, 80, 30, "Test");

    // Create a button labeled "Close"
    Fl_Button *btn2 = new Fl_Button(120, 410, 80, 30, "Close");

    // Set the callback function for the button
    btn1->callback(testCallback);
    btn2->callback(closeCallback);

    win.end();
    win.resizable(table);
    win.show(argc,argv);
    return(Fl::run());

}