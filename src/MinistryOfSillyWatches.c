#include <pebble.h>

static Window *window;
static BitmapLayer *bitmap_layer;
static GBitmap *icon_bitmap;
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

static void update_time(struct tm *tick_time) {
  int hour;
  strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
  icon_bitmap = gbitmap_create_with_resource(RESOURCE_ID_FACE_00);
  switch((hour = tick_time->tm_sec % 12)) {
  case 0:
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%d: showing face %p", hour, face_00_bitmap);
    bitmap_layer_set_bitmap(bitmap_layer, face_00_bitmap);
    break;
  case 1:
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%d: showing face %p", hour, face_01_bitmap);
    bitmap_layer_set_bitmap(bitmap_layer, face_01_bitmap);
    break;
  case 2:
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%d: showing face %p", hour, face_02_bitmap);
    bitmap_layer_set_bitmap(bitmap_layer, face_02_bitmap);
    break;
  case 3:
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%d: showing face %p", hour, face_03_bitmap);
    bitmap_layer_set_bitmap(bitmap_layer, face_03_bitmap);
    break;
  case 4:
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%d: showing face %p", hour, face_04_bitmap);
    bitmap_layer_set_bitmap(bitmap_layer, face_04_bitmap);
    break;
  case 5:
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%d: showing face %p", hour, face_05_bitmap);
    bitmap_layer_set_bitmap(bitmap_layer, face_05_bitmap);
    break;
  case 6:
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%d: showing face %p", hour, face_06_bitmap);
    bitmap_layer_set_bitmap(bitmap_layer, face_06_bitmap);
    break;
  case 7:
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%d: showing face %p", hour, face_07_bitmap);
    bitmap_layer_set_bitmap(bitmap_layer, face_07_bitmap);
    break;
  case 8:
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%d: showing face %p", hour, face_08_bitmap);
    bitmap_layer_set_bitmap(bitmap_layer, face_08_bitmap);
    break;
  case 9:
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%d: showing face %p", hour, face_09_bitmap);
    bitmap_layer_set_bitmap(bitmap_layer, face_09_bitmap);
    break;
  case 10:
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%d: showing face %p", hour, face_10_bitmap);
    bitmap_layer_set_bitmap(bitmap_layer, face_10_bitmap);
    break;
  case 11:
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%d: showing face %p", hour, face_11_bitmap);
    bitmap_layer_set_bitmap(bitmap_layer, face_11_bitmap);
    break;
  default:
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%d: showing face %p", hour, face_00_bitmap);
    bitmap_layer_set_bitmap(bitmap_layer, icon_bitmap);
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

  icon_bitmap = gbitmap_create_with_resource(RESOURCE_ID_ICON);
  face_00_bitmap = gbitmap_create_with_resource(RESOURCE_ID_FACE_00);
  face_01_bitmap = gbitmap_create_with_resource(RESOURCE_ID_FACE_01);
  face_02_bitmap = gbitmap_create_with_resource(RESOURCE_ID_FACE_02);
  face_03_bitmap = gbitmap_create_with_resource(RESOURCE_ID_FACE_03);
  face_04_bitmap = gbitmap_create_with_resource(RESOURCE_ID_FACE_04);
  face_05_bitmap = gbitmap_create_with_resource(RESOURCE_ID_FACE_05);
  face_06_bitmap = gbitmap_create_with_resource(RESOURCE_ID_FACE_06);
  face_07_bitmap = gbitmap_create_with_resource(RESOURCE_ID_FACE_07);
  face_08_bitmap = gbitmap_create_with_resource(RESOURCE_ID_FACE_08);
  face_09_bitmap = gbitmap_create_with_resource(RESOURCE_ID_FACE_09);
  face_10_bitmap = gbitmap_create_with_resource(RESOURCE_ID_FACE_10);
  face_11_bitmap = gbitmap_create_with_resource(RESOURCE_ID_FACE_11);
  bitmap_layer = bitmap_layer_create(bounds);
  bitmap_layer_set_bitmap(bitmap_layer, icon_bitmap);

  update_time(tick_time);

  layer_add_child(window_layer, bitmap_layer_get_layer(bitmap_layer));
}

static void window_unload(Window *window) {
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
