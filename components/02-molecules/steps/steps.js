Drupal.behaviors.steps = {
  attach() {
    const tnsSlider = tns({
      container: '.steps__container',
      arrowkeys: true,
      center: true,
      controls: false,
      items: 1,
      loop: false,
      mouseDrag: true,
      nav: false,
      slideBy: 'page',
      responsive: {
        720: {
          items: 2,
          center: true,
          fixedWidth: 580,
        },
        1224: {
          items: 1,
          disable: true,
        },
      },
    });

    const info = tnsSlider.getInfo();

    // Ensure unique only unique IDs are shown
    document.querySelector('.tns-outer').id = 'outterStepCarousel';
    document.querySelector('.tns-inner').id = 'innerStepCarousel';
    document.querySelector('.tns-ovh').id = 'outterStepVisuallyHidden';

    // Steps pager
    // gets initial pager and liveregion values
    const counter = document.querySelector('.steps__pager');
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
      document.querySelector(`.steps__${value}`).onclick = () => {
        tnsSlider.pause();
        tnsSlider.goTo(value);
      };
    });

    // Rebuild slider on breakpoint to adjust to new display
    tnsSlider.events.on('newBreakpointStart', () => {
      tnsSlider.rebuild();
    });
  },
};
