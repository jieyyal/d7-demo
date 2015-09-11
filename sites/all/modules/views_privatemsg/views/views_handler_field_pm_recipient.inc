<?php


class views_handler_field_pm_recipient extends views_handler_field_entity {

  function option_definition() {
    $options = parent::option_definition();
    $options['count'] = array('default' => '0', 'translatable' => TRUE);
    $options['padding_text'] = array(
      'default' => '...',
      'translatable' => TRUE
    );
    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['count'] = array(
      '#type' => 'textfield',
      '#title' => t('How many recipients to show'),
      '#default_value' => $this->options['count'],
    );
    $form['padding_text'] = array(
      '#type' => 'textfield',
      '#title' => t('Padding text'),
      '#default_value' => $this->options['padding_text'],
    );
    parent::options_form($form, $form_state);

  }

  function render($values) {
    if ($entity = $this->get_value($values)) {
      $thread_id = $entity->thread_id;
      $participants = _privatemsg_load_thread_participants($thread_id, FALSE, FALSE, 'view');
      $participant_count = count($participants);
      $default_count = $this->options['count'];
      if ($default_count != 0) {
        $participants = array_slice($participants, 0, $default_count);
      }
      $participant_names = array();
      foreach ($participants as $participant) {
        if ($participant->type == 'user') {
          $account = user_load($participant->recipient);
          if (isset($account->field_chinese_name[LANGUAGE_NONE][0]['value'])) {
            $participant_names[] = $account->field_chinese_name[LANGUAGE_NONE][0]['value'];
          }
          else {
            $participant_names[] = $participant->name;
          }
        }
        else {
          $participant_names[] = $participant->name;
        }
      }
      $participant_text = implode(" , ", $participant_names);
      if ($default_count != 0 && $participant_count > $default_count) {
        $participant_text .= " , " . $this->options['padding_text'];
      }
      return $participant_text;
    }
  }
}