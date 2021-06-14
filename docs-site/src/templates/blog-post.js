import * as React from "react";
import { Link, graphql } from "gatsby";

import Seo from "../components/seo";
import TitleBar from "../components/titlebar";
import ArticleHeader from "../components/article-header";
import "katex/dist/katex.min.css";
import UIkit from "uikit";
import Icons from 'uikit/dist/js/uikit-icons';

const BlogPostTemplate = ({ data }) => {
  const post = data.markdownRemark;
  const siteTitle = data.site.siteMetadata?.title || `Title`;
  const { previous, next } = data;
  UIkit.use(Icons);



  return (
    <div>
      <TitleBar />
      <Seo
        title={post.frontmatter.title}
        description={post.frontmatter.description || post.excerpt}
      />
      <ArticleHeader title={post.frontmatter.title} imgURL={data.file ? data.file.publicURL : ""}/>
      <div className="uk-container uk-margin-top">
        <article
          className="blog-post"
          itemScope
          itemType="http://schema.org/Article"
        >
          <header>
            <h1 itemProp="headline">{post.frontmatter.title}</h1>
            <p>{post.frontmatter.date}</p>
          </header>
          <a href={`https://github.com/dmharrington03/physics/tree/master/${post.frontmatter.title.replace(/\s+/g, '')}`}
            id="coolButton" 
            className="uk-button uk-button-default uk-margin-bottom"
            target="_blank"
          >
            <span data-uk-icon="github"></span>
            &nbsp;View on Github
          </a>
          <section
            dangerouslySetInnerHTML={{ __html: post.html }}
            itemProp="articleBody"
          />
          <hr />
        </article>
        <nav className="blog-post-nav">
          <ul
            style={{
              display: `flex`,
              flexWrap: `wrap`,
              justifyContent: `space-between`,
              listStyle: `none`,
              padding: 0,
            }}
          >
            <li>
              {previous && (
                <a href={previous.fields.slug} rel="prev"
                  className="uk-button uk-button-default uk-margin=bottom"
                  id="coolButton">
                  ← {previous.frontmatter.title}
                </a>
              )}
            </li>
            <li>
              {next && (
                <a href={next.fields.slug} rel="next"
                  className="uk-button uk-button-default uk-margin=bottom"
                  id="coolButton">
                  {next.frontmatter.title} →
                </a>
              )}
            </li>
          </ul>
        </nav>
      </div>


      <footer class="uk-height-small uk-flex uk-flex-center 
              uk-background-secondary uk-flex-column
              uk-flex-middle uk-light">
          <p>Daniel Harrington</p>
          <ul class="uk-iconnav">
            <li><a href="https://github.com/dmharrington03" 
              data-uk-icon="icon: github-alt; ratio: 1.2"
              target="_blank"></a>
            </li>
          </ul>
      </footer>
    </div>
  );
};

export default BlogPostTemplate;

export const pageQuery = graphql`
  query BlogPostBySlug(
    $id: String!
    $title: String
    $previousPostId: String
    $nextPostId: String
  ) {
    site {
      siteMetadata {
        title
      }
    }
    file(name: {eq: $title }, relativeDirectory: {eq: "header-images"}) {
      publicURL
    }
    markdownRemark(id: { eq: $id }) {
      id
      excerpt(pruneLength: 160)
      html
      frontmatter {
        title
        date(formatString: "MMMM DD, YYYY")
        description
      }
    }
    previous: markdownRemark(id: { eq: $previousPostId }) {
      fields {
        slug
      }
      frontmatter {
        title
      }
    }
    next: markdownRemark(id: { eq: $nextPostId }) {
      fields {
        slug
      }
      frontmatter {
        title
      }
    }
  }
`;
