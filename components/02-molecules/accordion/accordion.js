Drupal.behaviors.accordion = {
  attach(context) {
    // Polyfill for SVG classList IE11 support.
    if (
      !(
        'classList' in
        document.createElementNS('http://www.w3.org/2000/svg', 'g')
      )
    ) {
      const descr = Object.getOwnPropertyDescriptor(
        HTMLElement.prototype,
        'classList',
      );
      Object.defineProperty(SVGElement.prototype, 'classList', descr);
    }

    const accordion = context.querySelector('.accordion');
    const accordionList = context.querySelector('.accordion__list');
    const accordionItems = context.querySelectorAll('.accordion__item');
    const accordionButtons = context.querySelectorAll('.accordion__button');
    const accordionContents = context.querySelectorAll('.accordion__content');
    const accordionButtonIcon = context.querySelectorAll('.accordion__icon');
    let activeIndex = 0;

    function toggleAccordion(index) {
      if (index === activeIndex) {
        accordionContents[index].classList.toggle('is-active');
        if (
          accordionContents[index].getAttribute('aria-expanded') === 'false'
        ) {
          accordionButtonIcon[index].classList.add('rotate__icon');
          accordionContents[index].setAttribute('aria-expanded', 'true');
        } else {
          accordionContents[index].setAttribute('aria-expanded', 'false');
          accordionButtonIcon[index].classList.remove('rotate__icon');
        }
        return;
      }

      if (index >= 0 && index <= accordionContents.length) {
        accordionContents[activeIndex].classList.remove('is-active');
        accordionContents[index].classList.add('is-active');

        accordionContents[activeIndex].setAttribute('aria-expanded', 'false');
        accordionContents[index].setAttribute('aria-expanded', 'true');

        accordionButtonIcon[activeIndex].classList.remove('rotate__icon');
        accordionButtonIcon[index].classList.add('rotate__icon');

        activeIndex = index;
      }
    }

    function handleClick(element, index) {
      element.addEventListener('click', e => {
        e.preventDefault();
        toggleAccordion(index);
      });
    }

    for (let i = 0; i < accordionButtons.length; i++) {
      handleClick(accordionButtons[i], i);
    }

    for (let i = 0; i < accordionContents.length; i++) {
      accordionContents[i].setAttribute('aria-expanded', 'false');
    }

    if (accordion.classList.contains('accordion--two-col')) {
      for (let i = 0; accordionList.length; i++) {
        accordionList.removeChild(accordionList[i]);
      }

      const half = Math.ceil(accordionItems.length / 2);
      const tmpAccordionList = Array.from(accordionItems);
      const firstAccordionColumn = tmpAccordionList.splice(0, half);
      const secondAccordionColumn = tmpAccordionList.splice(-half);

      const firstColumn = document.createElement('li');
      const secondColumn = document.createElement('li');

      firstColumn.classList.add('accordion__firstColumn');
      secondColumn.classList.add('accordion__secondColumn');

      const firstList = document.createElement('ul');
      const secondList = document.createElement('ul');

      for (let i = 0; i < firstAccordionColumn.length; i++) {
        firstList.appendChild(firstAccordionColumn[i]);
      }

      for (let i = 0; i < secondAccordionColumn.length; i++) {
        secondList.appendChild(secondAccordionColumn[i]);
      }

      firstColumn.appendChild(firstList);
      secondColumn.appendChild(secondList);

      accordionList.appendChild(firstColumn);
      accordionList.appendChild(secondColumn);
    }
  },
};
