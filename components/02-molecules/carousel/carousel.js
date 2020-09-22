Drupal.behaviors.carousel = {
  attach() {
    const tnsSlider = tns({
      container: '.slide__container',
      arrowKeys: true,
      controls: false,
      nav: true,
      speed: 1000,
      navContainer: '.slide__nav-menu',
      autoplay: true,
      autoplayButton: '.slide__autoplay',
      autoplayHoverPause: true,
      autoplayTimeout: 8000,
      autoplayText: [
        '<svg><use xlink:href="/themes/custom/asebac/dist/icons.svg#play"></use></svg>',
        '<svg><use xlink:href="/themes/custom/asebac/dist/icons.svg#pause"></use></svg>',
      ],
    });

    const info = tnsSlider.getInfo();

    // Ensure unique only unique IDs are shown
    document.querySelector('.tns-outer').id = 'outterCarousel';
    document.querySelector('.tns-inner').id = 'innerCarousel';
    document.querySelector('.tns-ovh').id = 'outterVisuallyHidden';

    // Carousel pager
    // gets initial pager and liveregion values
    const counter = document.querySelector('.slide__pager');
    counter.textContent = `${info.displayIndex} / ${info.slideCount}`;
    const liveregion = document.querySelector('.tns-liveregion');

    // updates values on the start of each transition
    tnsSlider.events.on('transitionEnd', data => {
      const { displayIndex, slideCount } = data;
      counter.textContent = `${displayIndex} / ${slideCount}`;
      liveregion.textContent = `Item ${displayIndex} de ${slideCount}`;
    });

    // Custom Navigation Controls
    const controlValues = ['prev', 'next'];

    controlValues.forEach(value => {
      document.querySelector(`.slide__${value}`).onclick = () => {
        tnsSlider.pause();
        tnsSlider.goTo(value);
      };
    });

    // Tabindex info for Slide CTAs
    const listIterator = (list, attribute) => {
      for (let index = 0; index < list.length; index++) {
        list[index].setAttribute('tabindex', attribute);
      }
    };

    // selects all ctas
    const buttonList = document.querySelectorAll('.tns-item .button');
    listIterator(buttonList, '-1');

    // selects currently displayed ctas
    const activeSlide = document.querySelector('.tns-slide-active');
    const activeButtons = activeSlide.querySelectorAll('.button');
    listIterator(activeButtons, '0');

    // updates cta's tabindex on when changes to next slide
    tnsSlider.events.on('transitionEnd', data => {
      const { indexCached, displayIndex } = data;
      listIterator(
        data.slideItems[indexCached].querySelectorAll('.button'),
        '-1',
      );

      listIterator(
        data.slideItems[displayIndex].querySelectorAll('.button'),
        '0',
      );
    });

    // Carousel Nav Pagination
    // initial translation
    const navMenu = document.querySelector('.slide__nav-menu');
    navMenu.ariaLabel = 'Paginacion del Carousel';

    const navMenuListItems = navMenu.querySelectorAll('li');
    const navMenuItems = navMenu.querySelectorAll('button');

    for (let index = 0; index < navMenuItems.length; index++) {
      navMenuListItems[index].removeAttribute('aria-label');
      navMenuItems[index].ariaLabel = `Item ${index + 1}`;
      navMenuItems[index].setAttribute('tabindex', 0);
    }

    document
      .querySelector('.tns-nav-active')
      .insertAdjacentHTML(
        'beforeend',
        '<span class="nav-active visuallyhidden">(Item Actual)</span>',
      );

    // translation on transition
    tnsSlider.events.on('transitionStart', () => {
      document
        .querySelector('.tns-nav-active')
        .insertAdjacentElement(
          'beforeend',
          document.querySelector('.nav-active.visuallyhidden'),
        );

      for (let index = 0; index < navMenuItems.length; index++) {
        navMenuListItems[index].removeAttribute('aria-label');
        navMenuItems[index].setAttribute('tabindex', 0);
        navMenuItems[index].ariaLabel = `Item ${index + 1}`;
      }
    });
  },
};
