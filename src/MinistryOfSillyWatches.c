#include <pebble.h>

static Window *window;
static BitmapLayer *bitmap_layer;
static GBitmap *face_0_bitmap;
static GBitmap *face_1_bitmap;
static GBitmap *face_2_bitmap;
static GBitmap *face_3_bitmap;
static GBitmap *face_4_bitmap;
static GBitmap *face_5_bitmap;
static GBitmap *face_6_bitmap;
static GBitmap *face_7_bitmap;
static GBitmap *face_8_bitmap;
static GBitmap *face_9_bitmap;
static GBitmap *face_10_bitmap;
static GBitmap *face_11_bitmap;

#define SET_FACE(FACE_ID) do {						\
  if (!face_ ## FACE_ID ## _bitmap) {					\
    face_ ## FACE_ID ## _bitmap =					\
      gbitmap_create_with_resource(RESOURCE_ID_FACE_ ## FACE_ID);	\
    if (!face_ ## FACE_ID ## _bitmap) {					\
      APP_LOG(APP_LOG_LEVEL_ERROR, "%d: face allocation error for %d",	\
	  FACE_ID, RESOURCE_ID_FACE_ ## FACE_ID);			\
    }									\
  }									\
  APP_LOG(APP_LOG_LEVEL_DEBUG, "%d: showing face %p",			\
      FACE_ID, face_ ## FACE_ID ## _bitmap);				\
  bitmap_layer_set_bitmap(bitmap_layer, face_ ## FACE_ID ## _bitmap);	\
} while(0)

static void update_time(struct tm *tick_time) {
  int hour;
  switch((hour = tick_time->tm_sec % 12)) {
  case 0:
    SET_FACE(0);
    break;
  case 1:
    SET_FACE(1);
    break;
  case 2:
    SET_FACE(2);
    break;
  case 3:
    SET_FACE(3);
    break;
  case 4:
    SET_FACE(4);
    break;
  case 5:
    SET_FACE(5);
    break;
  case 6:
    SET_FACE(6);
    break;
  case 7:
    SET_FACE(7);
    break;
  case 8:
    SET_FACE(8);
    break;
  case 9:
    SET_FACE(9);
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
  if (face_0_bitmap) {
    gbitmap_destroy(face_0_bitmap);
  }
  if (face_1_bitmap) {
    gbitmap_destroy(face_1_bitmap);
  }
  if (face_2_bitmap) {
    gbitmap_destroy(face_2_bitmap);
  }
  if (face_3_bitmap) {
    gbitmap_destroy(face_3_bitmap);
  }
  if (face_4_bitmap) {
    gbitmap_destroy(face_4_bitmap);
  }
  if (face_5_bitmap) {
    gbitmap_destroy(face_5_bitmap);
  }
  if (face_6_bitmap) {
    gbitmap_destroy(face_6_bitmap);
  }
  if (face_7_bitmap) {
    gbitmap_destroy(face_7_bitmap);
  }
  if (face_8_bitmap) {
    gbitmap_destroy(face_8_bitmap);
  }
  if (face_9_bitmap) {
    gbitmap_destroy(face_9_bitmap);
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
