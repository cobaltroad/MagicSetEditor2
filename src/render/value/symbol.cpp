//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) Twan van Laarhoven and the other MSE developers          |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

// ----------------------------------------------------------------------------- : Includes

#include <util/prec.hpp>
#include <util/io/package.hpp>
#include <render/value/symbol.hpp>
#include <render/symbol/filter.hpp>
#include <data/symbol.hpp>
#include <gui/util.hpp> // draw_checker
#include <util/error.hpp>

// ----------------------------------------------------------------------------- : SymbolValueViewer

IMPLEMENT_VALUE_VIEWER(Symbol);

void SymbolValueViewer::draw(RotatedDC& dc) {
  drawFieldBorder(dc);
  // draw checker background
  draw_checker(dc, dc.getInternalRect());
  double wh = min(dc.getWidth(), dc.getHeight());
  // try to load symbol
  if (symbols.empty() && !value().filename.empty()) {
    try {
      // load symbol
      SymbolP symbol = getLocalPackage().readFile<SymbolP>(value().filename);
      // aspect ratio
      double ar = symbol->aspectRatio();
      ar = min(style().max_aspect_ratio, max(style().min_aspect_ratio, ar));
      // render and filter variations
      FOR_EACH(variation, style().variations) {
        Image img = render_symbol(symbol, *variation->filter, variation->border_radius, int(200 * ar), 200);
        Image resampled(int(wh * ar), int(wh), false);
        resample(img, resampled);
        symbols.push_back(Bitmap(resampled));
      }
    } catch (const Error& e) {
      handle_error(e);
    }
  }
  // draw image, if any
  int x = 0;
  for (size_t i = 0 ; i < symbols.size() ; ++i) {
    // todo : labels?
    dc.DrawBitmap(symbols[i], RealPoint(x, 0));
    x += symbols[i].GetWidth() + 2;
  }
}

void SymbolValueViewer::onValueChange() {
  symbols.clear();
}
