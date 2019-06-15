#ifndef UI_SRC_TEXTGUI_H_
#define UI_SRC_TEXTGUI_H_

namespace balcony_watering_system {
namespace ui {

class TextGui {
public:
  TextGui();
  virtual ~TextGui();

  void run();

private:
  void doStartPump();
  void doStopPump();
};

} /* namespace ui */
} /* namespace balcony_watering_system */

#endif /* UI_SRC_TEXTGUI_H_ */
