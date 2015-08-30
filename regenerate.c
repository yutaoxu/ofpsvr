/*
 * P.S.V.R 的软件实验室
 * 版权所有 (C) 2009-2015  P.S.V.R
 * 
 * 本程序为自由软件；您可依据自由软件基金会所发表的 GNU 通用公共授权条款，对本程序进行
 * 再发布和/或修改；无论您依据的是本授权的第三版，还是（您可选的）任一日后发行的版本。
 * 
 * 本程序是基于实用的目的而加以发布的，然而并不承担任何担保责任；亦不对适售性或特定目的
 * 的适用性做出默示性担保。详情请参照 GNU 通用公共授权。
 * 
 * 您应该已经收到了附随于本程序的 GNU 通用公共授权的副本；如果没有，请参照
 * <http://www.gnu.org/licenses/>.
 * 
 * OF P.S.V.R
 * Copyright (C) 2009-2015  P.S.V.R
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ofpsvr.h"
#include <openssl/md5.h>

#define OFPSVR_HEADER1 "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"\
             "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\" \"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">"\
             "<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\" >"\
             "<head>"\
             "<meta http-equiv=\"Content-type\" content=\"text/html; charset=UTF-8\" />"\
             "<link href=\"%s/css/master.css\" media=\"screen\" rel=\"stylesheet\" type=\"text/css\" />"\
             "<script id=\"master_js\" src=\"%s/js/master.js\" type=\"text/javascript\"></script>"\
             "<script type=\"text/x-mathjax-config\">"\
               "MathJax.Hub.Config({"\
               "  tex2jax: {"\
               "    inlineMath: [ ['$','$'] ],"\
               "    processEscapes: true"\
               "  }"\
               "});"\
              "</script>  "\
              "<style type=\"text/css\" media=\"screen\">"\
              " .post_body p{"\
              "   text-indent:20px;"\
              "   margin-bottom:10px;"\
              " }"\
              "</style>"\
             "<link href=\"/blog.xml\" type=\"application/rss+xml\" rel=\"alternate\" title=\"Blog Of P.S.V.R RSS Feed\" />"\
             "<script type=\"text/javascript\" src=\"http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML\"></script>"
#define OFPSVR_HEADER2 "</head>"\
             "<body>"\
             "<a href=\"https://github.com/pmq20/ofpsvr\"><img style=\"position: absolute; top: 0; right: 0; border: 0;\" src=\"%s/img/forkme.png\" alt=\"Fork me on GitHub\"></a>"\
             "<div id=\"top\"><div id=\"logo\"><a href=\"/blog\"><img alt=\"Logo\" src=\"%s/img/logo.png\" /></a><a href=\"/blog\"><img alt=\"Logo\" src=\"%s/img/logo2.png\" /></a></div></div>"\
             "<table id=\"content\"><tr>"\
             "<!-- ======Content====== -->"\
             "<td id=\"main\">"
#define OFPSVR_FOOTER  "</td>"\
             "<td id=\"sidebar\"><ul>"\
             "<li><h2>关于我</h2><div id=\"about_me\" class=\"body\"><img alt=\"P.S.V.R\" id=\"psvr\" class=\"illustration\" src=\"%s/img/me.jpg\" />大家好, 我叫 <strong>P.S.V.R</strong>, 专注于开发易于使用、健壮鲁棒、文档清晰的高品质软件。<br style=\"clear:both\" /><strong>曾用名</strong>: Pan 平底锅 试管牛<br /><strong>衍生名</strong>: 平底牛 试管锅 事故按钮 ...</div></li>"\
             "<li><h2>订阅</h2><div class=\"body\"><a href=\"/blog.xml\"><img id=\"rss\" alt=\"rss\" width=\"200\" height=\"173\" src=\"%s/img/rss.png\" /></a></div></li>"\
             "<li><h2>联系我</h2><div class=\"body\"><ul><li><img alt=\"address\" src=\"%s/img/email.png\" /></li></ul></div></li>"\
             "</ul></td>"\
             "<!-- ======Content====== -->"\
             "</tr></table>"\
             "<div id=\"foot\"><p style=\"font-size: 12px;\">本站由 <a href=\"https://github.com/pmq20/ofpsvr\">ofpsvr v8.9.0.2</a> 强力驱动.</p>"\
             "<div id=\"foot2\"></div></div>"\
             "<script type=\"text/javascript\">"\
             "  (function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){"\
             "  (i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),"\
             "  m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)"\
             "  })(window,document,'script','//www.google-analytics.com/analytics.js','ga');"\
             "  ga('create', 'UA-45613300-2', 'ofpsvr.org');"\
             "  ga('send', 'pageview');"\
             "</script>"\
             "</body>"\
             "</html>"
#define OFPSVR_RSS_HEADER "<?xml version=\"1.0\"?>"\
              "<rss version=\"2.0\">"\
              "<channel>"\
              "<title>Blog Of P.S.V.R</title>"\
              "<link>http://www.ofpsvr.com/blog</link>"\
              "<description>Blog Of P.S.V.R</description>"\
              "<language>zh-cn</language>"\
              "<docs>http://blogs.law.harvard.edu/tech/rss</docs>"\
              "<generator>OFPSVR Server</generator>"
#define OFPSVR_RSS_FOOTER "</channel>"\
              "</rss>"
void add_comment(struct Article *a, struct Comment *c)
{
        if (a->comments) {
                struct Comment *comment_ptr;
                for (comment_ptr = a->comments; comment_ptr->next;
                     comment_ptr = comment_ptr->next) {
                }
                comment_ptr->next = c;
        } else {
                a->comments = c;
        }
        ++a->comment_count;
}

static char *md5sum(char *src)
{
        char *ret = malloc(33 * sizeof(char));
        unsigned char *tmp = malloc(17 * sizeof(unsigned char));
        if (!ret || !tmp) {
                return 0;
        }
        MD5((unsigned char *)src, strlen(src), tmp);
        int i;
        char *now = ret;
        for (i = 0; i < 16; ++i) {
                sprintf(now, "%02x", tmp[i]);
                now += 2;
        }
        free(tmp);
        return ret;
}

char *fill_content(char *name, char *email, char *website, char *body,
                   long posted_at, int number)
{
        char *email_md5;
        char *ret;
        if (!(email_md5 = md5sum(email))) {
                return NULL;
        }
        if (posted_at % 2) {
                char *tmp_timestr = ofpsvr_timestr(posted_at);
                if (asprintf(&ret,
                             "<table class=\"a_comment\"><tr>"
                             "<td class=\"author author0\">"
                             "<div class=\"pic\"><img width=\"32\" height=\"32\" class=\"illustration\" alt=\"%s\" src=\"http://www.gravatar.com/avatar/%s?s=32&amp;d=http%%3A%%2F%%2Fwww.gravatar.com%%2Favatar%%2Fad516503a11cd5ca435acc9bb6523536%%3Fs%%3D32&amp;r=G\"/></div>"
                             "<div class=\"name\">%s%s%s%s%s</div>"
                             "</td>"
                             "<td class=\"commentbody\">"
                             "<div class=\"info\"><div class=\"info2\">"
                             "<div class=\"date\">发表于 %s | #%d</div>"
                             "<div class=\"maininfo\"><div class=\"maininfo2\"><p>%s</p></div></div>"
                             "</div></div>"
                             "</td>"
                             "</tr></table>",
                             name,
                             email_md5,
                             (website) ? "<a href=\"" : "",
                             (website) ? website : "",
                             (website) ? "\">" : "",
                             name,
                             (website) ? "</a>" : "",
                             tmp_timestr, number, body) < 0) {
                        return NULL;
                }
                free(tmp_timestr);
        } else {
                char *tmp_timestr = ofpsvr_timestr(posted_at);
                if (asprintf(&ret,
                             "<table class=\"a_comment\"><tr>"
                             "<td class=\"commentbody\">"
                             "<div class=\"info\"><div class=\"info2\">"
                             "<div class=\"date\">发表于 %s | #%d</div>"
                             "<div class=\"maininfo\"><div class=\"maininfo2\"><p>%s</p></div></div>"
                             "</div></div>"
                             "</td>"
                             "<td class=\"author author1\">"
                             "<div class=\"pic\"><img width=\"32\" height=\"32\" class=\"illustration\" alt=\"%s\" src=\"http://www.gravatar.com/avatar/%s?s=32&amp;d=http%%3A%%2F%%2Fwww.gravatar.com%%2Favatar%%2Fad516503a11cd5ca435acc9bb6523536%%3Fs%%3D32&amp;r=G\"/></div>"
                             "<div class=\"name\">%s%s%s%s%s</div>"
                             "</td>"
                             "</tr></table>",
                             tmp_timestr, number,
                             body,
                             name,
                             email_md5,
                             (website) ? "<a href=\"" : "",
                             (website) ? website : "",
                             (website) ? "\">" : "",
                             name, (website) ? "</a>" : "") < 0) {
                        return NULL;
                }
                free(tmp_timestr);
        }
        assert(email_md5);
        free(email_md5);
        cache_size += (strlen(ret) + 1) * sizeof(char);
        if (!cache_size_silent)
                WRITELOG("Cache Size: %lf MB (increased by fill_content)%s",
                         (double)cache_size / 1000000,
                         (running ? "\n" : "..."));
        return ret;
}

int regenerate(struct Article *x, int id)
{
        if (x->response) {
                MHD_destroy_response(x->response);
                cache_size -= x->page_sz;
                if (!cache_size_silent)
                        WRITELOG
                            ("Cache Size: %lf MB (decreased by regenerate)%s",
                             (double)cache_size / 1000000,
                             (running ? "\n" : "..."));
        }
        char *page, *old;
        char *tmp_timestr = ofpsvr_timestr(x->posted_at);
        if (asprintf(&page,
                     OFPSVR_HEADER1
                     "<title>%s - Blog Of P.S.V.R</title>"
                     OFPSVR_HEADER2
                     "<table class=\"post\"><tr>"
                     "<td class=\"post_bubble\"></td>"
                     "<td class=\"post_header\">"
                     "<h2 class=\"title\">%s</h2>"
                     "<p class=\"byline\">发表于 %s</p>"
                     "</td>"
                     "</tr><tr>"
                     "<td colspan=\"2\" class=\"post_body\">"
                     "%s"
                     "</td>"
                     "</tr></table>"
                     "<div class=\"intro\" style=\"margin-top:50px\">"
                     "<p><span class=\"bracket\">{</span> <span>%d</span> 个资源 <span class=\"bracket\">}</span></p>"
                     "</div>"
                     "<div id=\"resources_list_wrapper\">"
                     "<table id=\"resources_list\">"
                     "<thead>"
                     "<tr>"
                     "<td width=\"20%%\">编号</td>"
                     "<td width=\"60%%\">文件名</td>"
                     "<td width=\"20%%\">大小</td>"
                     "</tr>"
                     "</thead>"
                     "<tbody>",
                     asset_host, asset_host, /* OFPSVR_HEADER1 */
                     x->title,
                     asset_host, asset_host, asset_host, /* OFPSVR_HEADER2 */
                     x->title, tmp_timestr, x->body, x->resource_count) < 0) {
                return 0;
        }
        free(tmp_timestr);
        struct Resource *resource_ptr;
        int cnt = 0;
        for (resource_ptr = x->resources; resource_ptr;
             resource_ptr = resource_ptr->next) {
                ++cnt;
                old = page;
                char *ptr = strrchr(resource_ptr->filename, '.');
                if (asprintf
                    (&page,
                     "%s<tr><td>%d#</td><td><a class=\"%s\" href=\"/blog/%d/resources/%s\">%s</a></td><td>%lu KB</td></tr>",
                     old, cnt, ptr ? (ptr + 1) : "no_ext", id,
                     resource_ptr->filename, resource_ptr->filename,
                     resource_ptr->sz / 1000) < 0) {
                        return 0;
                }
                assert(old);
                free(old);
        }
        old = page;
        if (asprintf(&page,
                     "%s"
                     "</tbody>"
                     "</table>"
                     "</div>"
                     "<div class=\"intro\" style=\"margin-top:50px\">"
                     "<p><span class=\"bracket\">{</span> <span>%d</span> 条评论... 继续阅读 or <a rel=\"nofollow\" href=\"#comments_add\">添加一条</a> <span class=\"bracket\">}</span></p>"
                     "</div>", old, x->comment_count) < 0) {
                return 0;
        }
        assert(old);
        free(old);
        struct Comment *comment_ptr;
        for (comment_ptr = x->comments; comment_ptr;
             comment_ptr = comment_ptr->next) {
                old = page;
                if (asprintf(&page, "%s%s", old, comment_ptr->content) < 0) {
                        return 0;
                }
                assert(old);
                free(old);
        }
        old = page;
        if (asprintf(&page, "%s"
                     "<div class=\"intro\">"
                     "<p>您也随便说两句吧</p>"
                     "</div>"
                     "<form id=\"comments_add\" method=\"post\" onsubmit=\"return test_submit()\">"
                     "<p><input type=\"text\" tabindex=\"1\" size=\"22\" value=\"\" id=\"author\" name=\"reply[name]\"/>"
                     "<label for=\"author\">*昵称</label>"
                     "<p><input type=\"text\" tabindex=\"2\" size=\"22\" value=\"\" id=\"email\" name=\"reply[email]\"/>"
                     "<label for=\"email\">*E-mail (用于<a href=\"http://gravatar.com\">Gravatar</a>, 不会公开)</label></p>"
                     "<p><input type=\"text\" tabindex=\"3\" size=\"22\" value=\"\" id=\"url\" name=\"reply[website]\"/>"
                     "<label for=\"url\">您的网站（可选）</label></p>"
                     "<p><textarea tabindex=\"4\" rows=\"5\" cols=\"100\" id=\"comment\" name=\"reply[body]\"></textarea></p>"
                     "<p><input type=\"submit\" value=\"提交评论\" tabindex=\"5\" id=\"submit\" name=\"commit\"/></p>"
                     "</form>" OFPSVR_FOOTER, old,
                     asset_host, asset_host, asset_host /* OFPSVR_FOOTER */
                     ) < 0) {
                return 0;
        }
        assert(old);
        free(old);
        if (!
            (x->response =
             MHD_create_response_from_data(strlen(page), (void *)page, MHD_YES,
                                           MHD_NO))) {
                return 0;
        }
        if (MHD_NO ==
            (MHD_add_response_header
             (x->response, MHD_HTTP_HEADER_CONTENT_TYPE, "text/html"))) {
                return 0;
        }
        x->page_sz = (strlen(page) + 1) * sizeof(char);
        cache_size += x->page_sz;
        if (!cache_size_silent)
                WRITELOG("Cache Size: %lf MB (increased by regenerate)%s",
                         (double)cache_size / 1000000,
                         (running ? "\n" : "..."));
        return 1;
}

static char *count2bgcolor(int count)
{
        if (0 == count)
                return "#4ABBFF";
        else if (count > 0 && count <= 10)
                return "#388CBD";
        else if (count > 10 && count <= 50)
                return "#0F68A0";
        else if (count > 50 && count <= 100)
                return "#094469";
        else if (count > 100)
                return "black";
        else
                return "red";
}

static char *count2str(int count)
{
        char *ret;
        if (count < 1000) {
                if (asprintf(&ret, "%d", count) < 0)
                        return NULL;
        } else if (count < 1000000) {
                if (asprintf(&ret, "%dK", count / 1000) < 0)
                        return NULL;
        } else if (count < 1000000000) {
                if (asprintf(&ret, "%dM", count / 1000000) < 0)
                        return NULL;
        } else {
                if (asprintf(&ret, "%d", count) < 0)
                        return NULL;
        }
        assert(ret);
        return ret;
}

struct MHD_Response *generate_blog_response()
{
        char *page, *old;
        if (asprintf(&page,
                     OFPSVR_HEADER1
                     "<title>Blog Of P.S.V.R</title>" OFPSVR_HEADER2,
                     asset_host, asset_host, /* OFPSVR_HEADER1 */
                     asset_host, asset_host, asset_host /* OFPSVR_HEADER2 */
                     ) < 0) {
                return NULL;
        }
        int i;
        for (i = articles_len - 1; i >= 0; --i) {
                old = page;
                char *hit_count_str, *comment_count_str, *resource_count_str;
                if (!(hit_count_str = count2str(articles[i]->hit_count)))
                        return NULL;
                if (!
                    (comment_count_str = count2str(articles[i]->comment_count)))
                        return NULL;
                if (!
                    (resource_count_str =
                     count2str(articles[i]->resource_count)))
                        return NULL;
                char* tmp_timestr = ofpsvr_timestr(articles[i]->posted_at);
                if (asprintf(&page, "%s"
                             "<table class=\"post\"><tr>"
                             "<td class=\"post_boxes\">"
                             "<div class=\"box b_hits\"><div class=\"number\">%s</div><div>点击</div></div>"
                             "<div class=\"box b_replies\" style=\"background-color:%s\"><div class=\"number\">%s</div><div>评论</div></div>"
                             "<div class=\"box b_resources\"><div class=\"number\">%s</div><div>资源</div></div>"
                             "</td>"
                             "<td class=\"post_header\">"
                             "<h2 class=\"title\"><a href=\"/blog/%d\">%s</a></h2>"
                             "<p class=\"byline\">发表于 %s | #%d</p>"
                             "</td>"
                             "</tr><tr>"
                             "<td colspan=\"2\" class=\"post_body\">"
                             "<p>%s</p>"
                             "</td>"
                             "</tr></table>",
                             old,
                             hit_count_str,
                             count2bgcolor(articles[i]->comment_count),
                             comment_count_str, resource_count_str, i,
                             articles[i]->title, tmp_timestr, i,
                             articles[i]->introduction) < 0) {
                        return NULL;
                }
                free(tmp_timestr);
                assert(old);
                free(old);
                assert(hit_count_str);
                free(hit_count_str);
                assert(comment_count_str);
                free(comment_count_str);
                assert(resource_count_str);
                free(resource_count_str);
        }
        old = page;
        if (asprintf(&page, "%s" OFPSVR_FOOTER, old,
                     asset_host, asset_host, asset_host /* OFPSVR_FOOTER */
                     ) < 0) {
                return NULL;
        }
        assert(old);
        free(old);
        struct MHD_Response *ret;
        if (!
            (ret =
             MHD_create_response_from_data(strlen(page), (void *)page, MHD_YES,
                                           MHD_NO))) {
                return NULL;
        }
        if (MHD_NO ==
            MHD_add_response_header(ret, MHD_HTTP_HEADER_CONTENT_TYPE,
                                    "text/html")) {
                return NULL;
        }
        assert(ret);
        return ret;
}

struct MHD_Response *generate_blog_response_rss()
{
        char *page, *old;
        if (asprintf(&page,
                     OFPSVR_RSS_HEADER
                     "<pubDate>%s</pubDate>"
                     "<lastBuildDate>%s</lastBuildDate>",
                     articles[articles_len - 1]->rfc_posted_at,
                     articles[articles_len - 1]->rfc_posted_at) < 0) {
                return NULL;
        }
        int i;
        for (i = articles_len - 1; i >= 0; --i) {
                old = page;
                if (asprintf(&page, "%s"
                             "<item>"
                             "<title>%s</title>"
                             "<link>http://blog.ofpsvr.org/blog/%d</link>"
                             "<description>%s</description>"
                             "<pubDate>%s</pubDate>"
                             "</item>",
                             old,
                             articles[i]->title,
                             i,
                             articles[i]->body,
                             articles[i]->rfc_posted_at) < 0) {
                        return NULL;
                }
                assert(old);
                free(old);
        }
        old = page;
        if (asprintf(&page, "%s" OFPSVR_RSS_FOOTER, old) < 0) {
                return NULL;
        }
        assert(old);
        free(old);
        struct MHD_Response *ret;
        if (!
            (ret =
             MHD_create_response_from_data(strlen(page), (void *)page, MHD_YES,
                                           MHD_NO))) {
                return NULL;
        }
        if (MHD_NO ==
            MHD_add_response_header(ret, MHD_HTTP_HEADER_CONTENT_TYPE,
                                    "application/rss+xml")) {
                return NULL;
        }
        assert(ret);
        return ret;
}

// Pages passed to this function last for the whole life time of ofpsvr
static struct MHD_Response *response_static_page(const char *content)
{
        struct MHD_Response *response;
        if (!
            (response =
             MHD_create_response_from_data(strlen(content),
                                           (void *)content, MHD_NO,
                                           MHD_YES))) {
                WRITELOG
                    ("MHD_create_response_from_data failed at response_static_page.\n");
                exit(EXIT_FAILURE);
        }
        if (MHD_NO ==
            MHD_add_response_header(response,
                                    MHD_HTTP_HEADER_CONTENT_TYPE,
                                    "text/html")) {
                WRITELOG
                    ("MHD_add_response_header failed at response_static_page.\n");
                exit(EXIT_FAILURE);
        }
        return response;
}

void prepare_response_404()
{
        response_404 = response_static_page("<!DOCTYPE html>"
                                            "<html>"
                                            "<head>"
                                            "<meta charset=\"utf-8\">"
                                            "<title>- 哎呀! -</title>"
                                            "</head>"
                                            "<body>"
                                            "<h1>404 未找到</h1>"
                                            "<p>"
                                            "您请求的页面不存在。"
                                            "</p>"
                                            "<p>"
                                            "<a href=\"/\">返回首页</a>"
                                            "</p>" "</body>" "</html>");
}

void prepare_response_500()
{
        response_500 = response_static_page("<!DOCTYPE html>"
                                            "<html>"
                                            "<head>"
                                            "<meta charset=\"utf-8\">"
                                            "<title>- 哎呀! -</title>"
                                            "</head>"
                                            "<body>"
                                            "<h1>500 内部服务器错误</h1>"
                                            "<p>"
                                            "P.S.V.R 的软件实验室的程序遇到了一个意外的内部错误，导致无法完成该请求。"
                                            "</p><p>"
                                            "对您造成的不便我们深感歉意！本错误已经被记录在案，我们将尽快调查解决。"
                                            "</p>"
                                            "<p>"
                                            "<a href=\"/\">返回首页</a>"
                                            "</p>" "</body>" "</html>");
}

void prepare_response_index()
{
        char *page;
        if (asprintf(&page,
                     "<!DOCTYPE html>"
                     "<html>"
                     "    <head>"
                     "        <meta charset=\"utf-8\">"
                     "        <meta http-equiv=\"x-ua-compatible\" content=\"ie=edge\">"
                     "        <title>P.S.V.R 的软件实验室</title>"
                     "        <meta name=\"description\" content=\"P.S.V.R 的软件实验室\">"
                     "        <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
                     "        <link rel=\"apple-touch-icon\" href=\"%s/apple-touch-icon.png\">"
                     "        <link rel=\"stylesheet\" href=\"%s/css/ofpsvr.css\">"
                     "        <!--[if IE 6]><link rel=\"stylesheet\" type=\"text/css\" href=\"%s/css/ie6.css\" /><![endif]-->"
                     "    </head>"
                     "    <body>"
                     "        <div class=\"i\">"
                     "            <a href=\"/blog\"><img src=\"%s/img/index.png\" alt=\"P.S.V.R 的软件实验室\"></img></a>"
                     "            <p><a href=\"/blog\"><span class=\"welcome\">欢迎进入</span> P.S.V.R 的软件实验室</a></p>"
                     "        </div>"
                     "        <script>"
                     "            (function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){"
                     "            (i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),"
                     "            m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)"
                     "            })(window,document,'script','//www.google-analytics.com/analytics.js','ga');"
                     "            ga('create', 'UA-63776545-1', 'auto');"
                     "            ga('send', 'pageview');"
                     "        </script>"
                     "    </body>" "</html>",
                     asset_host, asset_host, asset_host, asset_host) < 0) {
                WRITELOG("sufficient space cannot be allocated in asprintf of prepare_resposnse_index");
                exit(EXIT_FAILURE);
        }
        response_index = response_static_page(page);
        free(page);
}

void prepare_response_favicon()
{
        if (!
            (response_favicon =
             MHD_create_response_from_data(favicon_ico_len,
                                           (void *)favicon_ico, MHD_YES,
                                           MHD_YES))) {
                WRITELOG
                    ("MHD_create_response_from_data failed at prepare_response_favicon.\n");
                exit(EXIT_FAILURE);
        }
        if (MHD_NO ==
            MHD_add_response_header(response_favicon,
                                    MHD_HTTP_HEADER_CONTENT_TYPE,
                                    "image/x-icon")) {
                WRITELOG
                    ("MHD_add_response_header failed at prepare_response_favicon.\n");
                exit(EXIT_FAILURE);
        }
        
}
