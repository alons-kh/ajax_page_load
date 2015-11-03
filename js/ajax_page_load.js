/**
 * @file
 * Provides JavaScript for ajax_page_load.
 */

(function ($) {
  "use strict";

  Drupal.behaviors.ajaxPageLoad = {
    attach: function (context, settings) {
      if (typeof NProgress === 'undefined') {
        return;
      }
      if (typeof Drupal.settings.ajax_page_load === 'undefined') {
        Drupal.settings.ajax_page_load = {cache: {}};
      }
      else {
        Drupal.settings.ajax_page_load.cache = {};
      }
      var current_url = window.location.pathname;
      NProgress.configure(Drupal.settings.ajax_page_load.pluginSettings);
      Drupal.settings.ajax_page_load.cache[current_url] = {
        title: $('title').html(),
        content: $(Drupal.settings.ajax_page_load.contentSelector)
      };

      $(Drupal.settings.ajax_page_load.links).unbind('click');
      $(Drupal.settings.ajax_page_load.links).click(function (e) {
        var url = $(this).attr('href');
        if ($(Drupal.settings.ajax_page_load.contentSelector).length === 0) {
          window.location.href = url;
        }
        loadPage(url);
        changeLinkClass($(this));
        window.history.pushState(null, null, url);
        e.preventDefault();
      });

      // Replace content, set page title.
      var replaceContent = function (page, url) {
        // Change page title.
        document.title = page.title;
        // Replace content.
        $(Drupal.settings.ajax_page_load.contentSelector).replaceWith(page.content);
        // Change meta tags.
        // Attach behaviors.
        Drupal.attachBehaviors($(Drupal.settings.ajax_page_load.contentSelector), settings);
      };

      // Get the page from the page cache or server; and process it.
      var loadPage = function (url) {
        progressStart();
        if (current_url === url) {
          progressDone();
        }
        else {
          if (Drupal.settings.ajax_page_load.cache[url]) {
            replaceContent(Drupal.settings.ajax_page_load.cache[url], url);
            progressDone();
          }
          else {
            $.ajax({
              url: url,
              success: function (data, textStatus, jqXHR) {
                var title = data.match(/<title>([^<]+)<\/title>/)[1];
                var content = $(data).find(Drupal.settings.ajax_page_load.contentSelector);
                if (content.length === 0) {
                  window.location.href = url;
                }
                Drupal.settings.ajax_page_load.cache[url] = {
                  title: title,
                  content: content
                };
                replaceContent(Drupal.settings.ajax_page_load.cache[url], url);
                progressDone();
              },
              error: function (jqXHR, textStatus, errorThrown) {
                document.location.href = url;
                return false;
              }
            });
          }
        }
      };

      // Set class active for clicked link.
      var changeLinkClass = function (el) {
        $(Drupal.settings.ajax_page_load.links + '.active').removeClass('active');
        el.addClass('active');
      };

      var progressStart = function () {
        NProgress.start();
        $('body').addClass('load').animate({opacity: Drupal.settings.ajax_page_load.opacity}, 500);
      };
      var progressDone = function () {
        NProgress.done();
        $('body').removeClass('load').animate({opacity: 1}, 500);
      };
    }
  };

})(jQuery);
