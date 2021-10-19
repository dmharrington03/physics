import * as React from "react";
import { graphql } from "gatsby";

import Seo from "../components/seo";
import TitleBar from "../components/titlebar";
import PageFooter from "../components/page-footer";
import UIkit from "uikit";
import Icons from 'uikit/dist/js/uikit-icons';


const About = ({ data }) => {

  const portraitURL = data.allFile.edges[0].node.publicURL;
  const codebgURL = data.allFile.edges[1].node.publicURL;

  UIkit.use(Icons);

  const bgPortraitStyle = {
    backgroundImage: `url(${portraitURL})`
  }

  const bgPortraitStyleSmall = {
    backgroundImage: `url(${portraitURL})`,
    backgroundColor: "#333333"
  }

  const bgMainStyle = {
    backgroundImage: `url(${codebgURL})`,
    backgroundColor: "#222222"
  }


  return (
    <div>
      <Seo title="Computational Physics" />
      <TitleBar />
      <div className="uk-flex uk-flex-center uk-grid">
          <div className="uk-width-expand uk-width-1-2@m uk-flex uk-flex-center uk-flex-middle uk-padding uk-visible@m">
            <div className="uk-width-2-3@m uk-width-2-3">
              <h1 className="uk-text-center uk-text-left@s">About Me</h1>
              <p>Hello! My name is Daniel Harrington. I'm currently a high school senior based in central Florida. I've always been interested in science, physics, and computer programming, but haven't always had a way to connect them. A few years ago, I applied to a summer program that asked for a portfolio of projects, and I realized that nothing I had done reflected the goals and things that I wanted to learn.</p>
              <p>I took advantage of pandemic free time and dove into more formal CS education, taking Harvard's CS50x course (highly recommend!) and studying on my own. At the same time, I started studying physics and realized I could use computer simulation to combine the two areas. I brushed up on C++ and started developing small exploratory projects that I catalogue here.
              In the future, I hope to study physics in college with an emphasis on computation. I love teaching and sharing with others, and this blog has been a great way to do it..</p>
            </div>
          </div>
          <div className="uk-width-expand uk-flex uk-flex-center uk-background-cover 
          uk-background-top-left uk-background-fixed uk-background-blend-soft-light uk-hidden@m uk-light" style={ bgPortraitStyleSmall }>
            <div className="uk-padding">
              <h1 className="uk-text-center uk-margin-top">About Me</h1>
              <div className="uk-container">
              <p>Hello! My name is Daniel Harrington. I'm currently a high school senior based in central Florida. I've always been interested in science, physics, and computer programming, but haven't always had a way to connect them. A few years ago, I applied to a summer program that asked for a portfolio of projects, and I realized that nothing I had done reflected the goals and things that I wanted to learn.</p>
              <p>I took advantage of pandemic free time and dove into more formal CS education, taking Harvard's CS50x course (highly recommend!) and studying on my own. At the same time, I started studying physics and realized I could use computer simulation to combine the two areas. I brushed up on C++ and started developing small exploratory projects that I catalogue here.
              In the future, I hope to study physics in college with an emphasis on computation. I love teaching and sharing with others, and this blog has been a great way to do it..</p>
              </div>
            </div>
          </div>
          <div className="uk-width-1-2@m uk-visible@s uk-background-image@m uk-background-cover uk-background-top-right" style={ bgPortraitStyle }></div>
      </div>
      <div className="uk-flex uk-flex-center
        uk-background-cover uk-background-blend-soft-light uk-light" style={ bgMainStyle }>
        <div className="uk-padding">
          <h1 className="uk-margin-top uk-text-center">About the Project</h1>
          <div className="uk-container">
            <h2>Format</h2>
            <p>For each topic of physics investigated, there are one or several programs demonstrating the corresponding theory through visualizations or simulations.</p>
            
            <p>Programs are written in C++ using the SFML framework. Though Python is often a popular choice for scientific uses, I chose C++ due its comparative speed and popularity in computer graphics. The main advantage of Python is the large amount of abstraction it offers both for mathematical and scientific computations, but since the goal of this project is to develop these tools from scratch, this is not an influential factor. In the future though, as I progress to more involved concepts, I may transition to Python through frameworks like Processing or SciPy.</p>
            
            <h2>Topics</h2>
            <p>Through this project, I aim to cover principles of physics presented in a calculus-based introductory physics course, as well as anything else that happens to interest me. Although the structure is not organized around any particular curriculum, material is loosely borrowed from MIT's 8.01 course and <i>University Physics</i> by Young and Freedman. Knowledge of basic calculus and programming principles are assumed in communication of concepts.</p>
            
            <h2>Download</h2>
            <p>If you wish to try any of the programs or build upon them, SFML must be installed on your platform.</p>
          </div>
        </div>
      </div>

      <PageFooter />
      
    </div>
  );
};

export default About;

export const pageQuery = graphql`
  query {
    site {
      siteMetadata {
        title
      }
    }
    allFile(filter: {name: {in: ["portrait", "codebg"]}}) {
      edges {
        node {
          publicURL
        }
      }
    }
  }
`;