// $Id$

Drupal.behaviors.nodeExpire = function(context) {
//   var min = new Date(Drupal.settings.minDate[0], Drupal.settings.minDate[1], Drupal.settings.minDate[3]);
  var max = Drupal.settings.maxDate;
  if (max) {
    max = new Date(max[0], max[1] -1, max[2]);
  }
  var min = Drupal.settings.minDate;
  min = new Date(min[0], min[1] -1, min[2]);
  $("#edit-expire").datepicker({
    dateFormat: Drupal.settings.dateFormat,
    minDate:    min,
    maxDate:    max
  });
}
