import React from 'react';

import { withKnobs, text } from '@storybook/addon-knobs';
import block from './block.twig';
import blockData from './block.yml';
import blockContact from './contact-block/contact-block.twig';
import blockContactData from './contact-block/contact-block.yml';

/**
 * Storybook Definition.
 */
export default { title: 'Molecules/Block', decorators: [withKnobs] };

export const basicBlockExample = () => {
  const heading = text('Heading', '¿Qué es el solidarismo?');
  blockData.block_heading = heading;

  return <div dangerouslySetInnerHTML={{ __html: block(blockData) }} />;
};

export const contactBlockExample = () => {
  return (
    <div dangerouslySetInnerHTML={{ __html: blockContact(blockContactData) }} />
  );
};
