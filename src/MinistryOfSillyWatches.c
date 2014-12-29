#include <pebble.h>

static Window *window;
static BitmapLayer *bitmap_layer;
static GBitmap *face_00_bitmap;
static GBitmap *face_01_bitmap;
static GBitmap *face_02_bitmap;
static GBitmap *face_03_bitmap;
static GBitmap *face_04_bitmap;
static GBitmap *face_05_bitmap;
static GBitmap *face_06_bitmap;
static GBitmap *face_07_bitmap;
static GBitmap *face_08_bitmap;
static GBitmap *face_09_bitmap;
static GBitmap *face_10_bitmap;
static GBitmap *face_11_bitmap;

#define SET_FACE(face) do {								\
  if (!face_ ## face ## _bitmap) {							\
    face_ ## face ## _bitmap = gbitmap_create_with_resource(RESOURCE_ID_FACE_ ## face);\
    if (!face_ ## face ## _bitmap) {							\
      APP_LOG(APP_LOG_LEVEL_ERROR, "%d: face allocation error for %d",		\
	  hour, RESOURCE_ID_FACE_ ## face);						\
    }											\
  }											\
  APP_LOG(APP_LOG_LEVEL_DEBUG, "%d: showing face %p", hour, face_00_bitmap);		\
  bitmap_layer_set_bitmap(bitmap_layer, face_00_bitmap);				\
} while(0)

static void update_time(struct tm *tick_time) {
  int hour;
  switch((hour = tick_time->tm_sec % 12)) {
  case 0:
    SET_FACE(00);
    break;
  case 1:
    SET_FACE(01);
    break;
  case 2:
    SET_FACE(02);
    break;
  case 3:
    SET_FACE(03);
    break;
  case 4:
    SET_FACE(04);
    break;
  case 5:
    SET_FACE(05);
    break;
  case 6:
    SET_FACE(06);
    break;
  case 7:
    SET_FACE(07);
    break;
  case 8:
    SET_FACE(08);
    break;
  case 9:
    SET_FACE(09);
    break;
  case 10:
    SET_FACE(10);
    break;
  case 11:
    SET_FACE(11);
    break;
  }
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time(tick_time);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  bitmap_layer = bitmap_layer_create(bounds);

  update_time(tick_time);

  layer_add_child(window_layer, bitmap_layer_get_layer(bitmap_layer));
}

static void window_unload(Window *window) {
  if (face_00_bitmap) {
    gbitmap_destroy(face_00_bitmap);
  }
  if (face_01_bitmap) {
    gbitmap_destroy(face_01_bitmap);
  }
  if (face_02_bitmap) {
    gbitmap_destroy(face_02_bitmap);
  }
  if (face_03_bitmap) {
    gbitmap_destroy(face_03_bitmap);
  }
  if (face_04_bitmap) {
    gbitmap_destroy(face_04_bitmap);
  }
  if (face_05_bitmap) {
    gbitmap_destroy(face_05_bitmap);
  }
  if (face_06_bitmap) {
    gbitmap_destroy(face_06_bitmap);
  }
  if (face_07_bitmap) {
    gbitmap_destroy(face_07_bitmap);
  }
  if (face_08_bitmap) {
    gbitmap_destroy(face_08_bitmap);
  }
  if (face_09_bitmap) {
    gbitmap_destroy(face_09_bitmap);
  }
  if (face_10_bitmap) {
    gbitmap_destroy(face_10_bitmap);
  }
  if (face_11_bitmap) {
    gbitmap_destroy(face_11_bitmap);
  }
  bitmap_layer_destroy(bitmap_layer);
}

static void init(void) {
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
  const bool animated = true;
  window_stack_push(window, animated);
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}

/*
 * vim: sw=2
 */
