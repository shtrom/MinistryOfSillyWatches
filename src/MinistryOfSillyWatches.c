#include <pebble.h>

static Window *window;
static BitmapLayer *bitmap_layer;
static GBitmap *face_bitmap;
static Layer *cane_layer;
static GPoint center;
static int cane_length;

#define SET_FACE(FACE_ID) do {							\
  GBitmap *old_face_bitmap = face_bitmap;					\
  face_bitmap = gbitmap_create_with_resource(RESOURCE_ID_FACE_ ## FACE_ID);	\
  if (!face_bitmap) {								\
    APP_LOG(APP_LOG_LEVEL_ERROR, "%d: face allocation error for %d",		\
	FACE_ID, RESOURCE_ID_FACE_ ## FACE_ID);					\
  }										\
  APP_LOG(APP_LOG_LEVEL_DEBUG, "%d: showing face %p",				\
      FACE_ID, face_bitmap);							\
  if (old_face_bitmap) {							\
    gbitmap_destroy(old_face_bitmap);						\
  }										\
} while(0)

static void load_face(struct tm *t) {
  switch(t->tm_hour % 12) {
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

static void update_time(struct tm *tick_time) {
  load_face(tick_time);
  bitmap_layer_set_bitmap(bitmap_layer, face_bitmap);
}

static void tick_handler(struct tm *t, TimeUnits units_changed) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "%d:%d:%d: unit changed %x",
      t->tm_hour, t->tm_min, t->tm_sec, (int)units_changed);

  if (units_changed & HOUR_UNIT) {
    update_time(t);
    vibes_double_pulse();
  }

  layer_mark_dirty(cane_layer);
}

static void cane_update_proc(struct Layer *layer, GContext *ctx) {
  GPoint cane;
  time_t now = time(NULL);
  struct tm *t = localtime(&now);

  int32_t angle = TRIG_MAX_ANGLE * (t->tm_min*60 + t->tm_sec) / 3600;
  cane.y = (int16_t)(-cos_lookup(angle) * (int32_t)cane_length / TRIG_MAX_RATIO) + center.y;
  cane.x = (int16_t)(sin_lookup(angle) * (int32_t)cane_length / TRIG_MAX_RATIO) + center.x;

  APP_LOG(APP_LOG_LEVEL_DEBUG, "%d:%d: rotating cane to %d",
      t->tm_min, t->tm_sec, (int)angle);

  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_draw_line(ctx, cane, center);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  bitmap_layer = bitmap_layer_create(bounds);
  load_face(tick_time);

  /* Calculated to be in a common area of all images;
   * See layer "Overlap" in resources/images/sillywalks/sillywalk.xcf
   */
  center.x = bounds.size.w * 67./144.;
  center.y = bounds.size.h * 93./168.;
  cane_length = center.x;
  cane_layer = layer_create(bounds);
  layer_set_update_proc(cane_layer, cane_update_proc);

  update_time(tick_time);
  layer_mark_dirty(cane_layer);

  layer_add_child(window_layer, bitmap_layer_get_layer(bitmap_layer));
  layer_add_child(window_layer, cane_layer);
}

static void window_unload(Window *window) {
  layer_destroy(cane_layer);
  bitmap_layer_destroy(bitmap_layer);

  gbitmap_destroy(face_bitmap);
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
